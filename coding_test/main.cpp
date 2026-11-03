#include <cstdio>
#include <string>
#include <vector>

struct Entity {
    std::string name;
    float health;
    float x, y;
};

class World {
  public:
    void Add(const std::string& name, float health, float x, float y) {
        entities.push_back({name, health, x, y});
    }

    // Damage every entity within `radius` of (cx, cy).
    void Explode(float cx, float cy, float radius, float damage) {
        for (auto e : entities) {
            float dx = e.x - cx, dy = e.y - cy;
            if (dx * dx + dy * dy < radius)
                e.health -= damage;
        }
    }

    // Remove dead entities.
    void Cleanup() {
        for (size_t i = 0; i < entities.size(); ++i) {
            if (entities[i].health <= 0)
                entities.erase(entities.begin() + i);
        }
    }

    const Entity* FindByName(const std::string& name) {
        for (auto& e : entities)
            if (e.name == name)
                return &e;
        return nullptr;
    }

    float AverageHealth() const {
        int total = 0;
        for (const auto& e : entities)
            total += e.health;
        return total / entities.size();
    }

    void Print() const {
        for (const auto& e : entities)
            printf("%s: %.1f\n", e.name.c_str(), e.health);
    }

    std::vector<Entity> entities;
};

int main() {
    World w;
    w.Add("orc", 50.f, 1.f, 1.f);
    w.Add("goblin", 30.f, 2.f, 0.f);
    w.Add("bat", 10.f, 0.5f, 0.5f);
    w.Add("troll", 120.f, 10.f, 10.f);

    const Entity* troll = w.FindByName("troll");

    w.Explode(0.f, 0.f, 3.f, 40.f);
    w.Cleanup();
    w.Print();

    printf("troll health: %.1f\n", troll->health);
    printf("average: %.1f\n", w.AverageHealth());
}