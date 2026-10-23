#include <iostream>
#include <string>
#include <tracy/Tracy.hpp>
#include <vector>

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
    Particle p{
        {
            0.1f,
            0.1f,
            0.1f,
        },
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f, 1.0f},
        5.0f,
        "particle",
        true,
    };
    std::vector<Particle> particles;
    {
        ZoneScopedN("Initialize particles");
        particles = std::vector<Particle>(100'000, p);
    }

    {
        ZoneScopedN("Loop over bad particles");
        for (int i = 0; i < 10'000; ++i) {
            {
                ZoneScopedN("Loop");
                for (auto& p : particles) {
                    if (!p.alive_)
                        continue;

                    p.pos_.x_ += p.vel_.x_ * delta_time;
                    p.lifetime_ -= delta_time;
                }
            }
        }
    }
}
} // namespace bad

namespace good {
struct Particle {
    Color color_;
    Vec3 pos_;
    Vec3 vel_;
    float lifetime_;
    bool alive_;
};

void run(float delta_time) {
    Particle p{
        {1.0f, 1.0f, 1.0f, 1.0f},
        {
            0.1f,
            0.1f,
            0.1f,
        },
        {1.0f, 1.0f, 1.0f},
        5.0f,
        true,
    };
    std::vector<Particle> particles;
    {
        ZoneScopedN("Initialize particles");
        particles = std::vector<Particle>(100'000, p);
    }

    {
        ZoneScopedN("Loop over bad particles");
        for (int i = 0; i < 10'000; ++i) {
            {
                ZoneScopedN("Loop");
                for (auto& p : particles) {
                    if (!p.alive_)
                        continue;

                    p.pos_.x_ += p.vel_.x_ * delta_time;
                    p.lifetime_ -= delta_time;
                }
            }
        }
    }
}
} // namespace good

int main() {
    float delta_time = 0.016f;
    bad::run(delta_time);
    good::run(delta_time);

    std::cout << "Bad: " << sizeof(bad::Particle)
              << " Good: " << sizeof(good::Particle) << std::endl;
    std::cout << "Press ENTER key..." << std::endl;
    std::getchar();

    return 0;
}
