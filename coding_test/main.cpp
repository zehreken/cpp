#include <chrono>
#include <cmath>
#include <cstdio>
#include <string>
#include <unordered_map>
#include <vector>

namespace original {
struct Particle {
    float x_, y_, z_;
    std::string tag_;
    float vx_, vy_, vz_;
    float life_;
};

std::vector<Particle> spawn(int n) {
    std::vector<Particle> ps;
    for (int i = 0; i < n; ++i) {
        Particle p;
        p.x_ = p.y_ = p.z_ = 0.f;
        p.vx_ = float(i % 7);
        p.vy_ = float(i % 5);
        p.vz_ = float(i % 3);
        p.life_ = float(i % 100) / 10.f;
        p.tag_ = "particle_" + std::to_string(i);
        ps.push_back(p);
    }
    return ps;
}

void update(std::vector<Particle>& ps, float dt) {
    for (auto& p : ps) {
        if (p.life_ > 0.f) {
            p.x_ += p.vx_ * dt;
            p.y_ += p.vy_ * dt;
            p.z_ += p.vz_ * dt;
            p.life_ -= dt;
        }
    }
}

float total_distance(std::vector<Particle> ps) {
    float sum = 0.f;
    for (size_t i = 0; i < ps.size(); ++i)
        sum += std::sqrt(
            ps[i].x_ * ps[i].x_ + ps[i].y_ * ps[i].y_ + ps[i].z_ * ps[i].z_
        );
    return sum;
}

int count_with_prefix(const std::vector<Particle>& ps, std::string prefix) {
    std::unordered_map<std::string, int> counts;
    for (auto p : ps)
        counts[p.tag_.substr(0, prefix.size())]++;
    return counts[prefix];
}

double
ms(std::chrono::steady_clock::time_point a,
   std::chrono::steady_clock::time_point b) {
    return std::chrono::duration<double, std::milli>(b - a).count();
}

void run() {
    using Clock = std::chrono::steady_clock;

    auto t0 = Clock::now();
    std::vector<Particle> ps = spawn(1'000'000);
    auto t1 = Clock::now();
    for (int frame = 0; frame < 60; ++frame)
        update(ps, 1.f / 60.f);
    auto t2 = Clock::now();
    float dist = total_distance(ps);
    auto t3 = Clock::now();
    int count = count_with_prefix(ps, "particle_1");
    auto t4 = Clock::now();

    printf("distance: %.0f\n", dist);
    printf("count:    %d\n", count);
    printf(
        "spawn %.1f ms | update %.1f ms | distance %.1f ms | count %.1f ms\n",
        ms(t0, t1),
        ms(t1, t2),
        ms(t2, t3),
        ms(t3, t4)
    );
}
} // namespace original

namespace improved {
struct Particles {
    std::vector<float> xs_, ys_, zs_, vxs_, vys_, vzs_, lifes_;
};

Particles spawn(size_t n) {
    Particles ps;
    ps.xs_.reserve(n); // Reserving improves, no unnecessary allocation
    ps.ys_.reserve(n);
    ps.zs_.reserve(n);
    ps.vxs_.reserve(n);
    ps.vys_.reserve(n);
    ps.vzs_.reserve(n);
    ps.lifes_.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        ps.xs_.push_back(0.0f);
        ps.ys_.push_back(0.0f);
        ps.zs_.push_back(0.0f);
        ps.vxs_.push_back(float(i % 7));
        ps.vys_.push_back(float(i % 5));
        ps.vzs_.push_back(float(i % 3));
        ps.lifes_.push_back(float(i % 100) / 10.f);
    }
    return ps;
}

void update(Particles& ps, float dt) {
    const size_t n = ps.xs_.size();
    float* xs = ps.xs_.data();
    float* ys = ps.ys_.data();
    float* zs = ps.zs_.data();
    float* vxs = ps.vxs_.data();
    float* vys = ps.vys_.data();
    float* vzs = ps.vzs_.data();
    float* lifes = ps.lifes_.data();
    for (size_t i = 0; i < n; ++i) {
        float alive = lifes[i] > 0.0f ? 1.0f : 0.0f;
        const float k = dt * alive;
        xs[i] += vxs[i] * k;
        ys[i] += vys[i] * k;
        zs[i] += vzs[i] * k;
        lifes[i] -= k;
    }
}

double total_distance(const Particles& ps) {
    double sum = 0.0;
    for (size_t i = 0; i < ps.xs_.size(); ++i)
        sum += std::sqrt(
            ps.xs_[i] * ps.xs_[i] + ps.ys_[i] * ps.ys_[i] +
            ps.zs_[i] * ps.zs_[i]
        );
    return sum;
}

int count_with_prefix(
    const std::vector<std::string>& tags, std::string_view prefix
) {
    // std::unordered_map<std::string, int> counts; // map is not needed
    int c = 0;
    for (const auto& tag : tags) {
        if (tag.starts_with(prefix)) {
            c++;
        }
    }
    return c;
}

double
ms(std::chrono::steady_clock::time_point a,
   std::chrono::steady_clock::time_point b) {
    return std::chrono::duration<double, std::milli>(b - a).count();
}

void run() {
    using Clock = std::chrono::steady_clock;

    const size_t n = 1'000'000;
    auto t0 = Clock::now();
    Particles ps = spawn(n);
    std::vector<std::string> tags;
    tags.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        tags.push_back("particle_" + std::to_string(i));
    }
    auto t1 = Clock::now();
    for (int frame = 0; frame < 60; ++frame)
        update(ps, 1.f / 60.f);
    auto t2 = Clock::now();
    double dist = total_distance(ps);
    auto t3 = Clock::now();
    int count = count_with_prefix(tags, "particle_1");
    auto t4 = Clock::now();

    printf("distance: %.0f\n", dist);
    printf("count:    %d\n", count);
    printf(
        "spawn %.1f ms | update %.1f ms | distance %.1f ms | count %.1f ms\n",
        ms(t0, t1),
        ms(t1, t2),
        ms(t2, t3),
        ms(t3, t4)
    );
}
} // namespace improved

int main() {
    original::run();
    improved::run();
}
