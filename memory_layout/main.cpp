#include <iostream>
#include <string>
#include <tracy/Tracy.hpp>
#include <vector>

constexpr size_t PARTICLE_COUNT = 100'000;
constexpr size_t LOOP_COUNT = 640;

// 12 bytes
struct Vec3 {
    float x_;
    float y_;
    float z_;
};

// 16 bytes
struct Color {
    float r_;
    float g_;
    float b_;
    float a_;
};

namespace bad {
struct Particle {
    Vec3 pos_;
    Vec3 vel_;
    Color color_;
    float lifetime_;
    std::string name_;
    bool alive_;
};

void run(float delta_time) {
    std::srand(31);
    std::vector<Particle> particles;
    {
        ZoneScopedN("Initialize bad particles");
        particles.reserve(PARTICLE_COUNT);
        for (size_t i = 0; i < PARTICLE_COUNT; ++i) {
            float lifetime = 1.0f + static_cast<float>(std::rand() % 10);
            particles.push_back(
                Particle{
                    {
                        0.1f,
                        0.1f,
                        0.1f,
                    },
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f, 1.0f},
                    lifetime,
                    "particle",
                    true,
                }
            );
        }
    }

    {
        ZoneScopedN("Loop over bad particles");
        for (size_t i = 0; i < LOOP_COUNT; ++i) {
            {
                ZoneScopedN("Bad/Loop");
                for (auto& p : particles) {
                    if (!p.alive_)
                        continue;

                    p.pos_.x_ += p.vel_.x_ * delta_time;
                    p.lifetime_ -= delta_time;
                    if (p.lifetime_ <= 0.0f) {
                        p.alive_ = false;
                    }
                }
            }
        }
    }
}
} // namespace bad

namespace good {
struct Particle {    // 44 bytes
    Color color_;    // 16 bytes
    Vec3 pos_;       // 12 bytes
    Vec3 vel_;       // 12 bytes
    float lifetime_; // 4 bytes
};

void run(float delta_time) {
    std::srand(31);
    std::vector<Particle> particles;
    {
        ZoneScopedN("Initialize good particles");
        particles.reserve(PARTICLE_COUNT);
        for (size_t i = 0; i < PARTICLE_COUNT; ++i) {
            float lifetime = 1.0f + static_cast<float>(std::rand() % 10);
            particles.push_back(
                Particle{
                    {1.0f, 1.0f, 1.0f, 1.0f},
                    {
                        0.1f,
                        0.1f,
                        0.1f,
                    },
                    {1.0f, 1.0f, 1.0f},
                    lifetime,
                }
            );
        }
    }

    size_t alive_count = PARTICLE_COUNT;
    {
        ZoneScopedN("Loop over good particles");
        for (size_t i = 0; i < LOOP_COUNT; ++i) {
            {
                ZoneScopedN("Good/Loop");
                for (size_t j = 0; j < alive_count;) {
                    Particle& p = particles[j];
                    p.pos_.x_ += p.vel_.x_ * delta_time;
                    p.lifetime_ -= delta_time;

                    if (p.lifetime_ <= 0.0f) {
                        std::swap(p, particles[--alive_count]);
                    } else {
                        ++j;
                    }
                }
            }
        }
    }
}
} // namespace good

int main() {
    float delta_time = 0.016f; // Simulates 60 fps
    bad::run(delta_time);
    good::run(delta_time);

    std::cout << "Bad: " << sizeof(bad::Particle)
              << " Good: " << sizeof(good::Particle) << std::endl;
    std::cout << "Press ENTER key..." << std::endl;
    std::getchar();

    return 0;
}
