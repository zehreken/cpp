#include <chrono>
#include <cmath>
#include <cstdio>
#include <string>
#include <unordered_map>
#include <vector>

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

int main() {
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

/*
distance: 4016178
count:    111111
spawn ~160–250 ms | update ~500 ms | distance ~100–550 ms | count ~50 ms
*/