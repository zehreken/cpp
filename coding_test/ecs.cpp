#include <cstdio>
#include <string>
#include <vector>

struct Entity {
    std::string name;
    float health;
    float x, y;
};

/*
orc: 10.0
troll: 120.0
troll health: 120.0
average: 65.0
*/

class World {
  public:
    void Add(const std::string& name, float health, float x, float y) {
        entities.push_back({name, health, x, y});
    }

    // Damage every entity within `radius` of (cx, cy).
    void Explode(float cx, float cy, float radius, float damage) {
        // Bug: Not changing the entity but creating copy here, fix is using a
        // ref
        for (auto& e : entities) {
            float dx = e.x - cx, dy = e.y - cy;
            // Bug: Should do sqrt(dx * dx + dy * dy) or even better we can
            // square radius
            if (dx * dx + dy * dy < radius * radius)
                e.health -= damage;
        }
    }

    // Remove dead entities.
    void Cleanup() {
        // Bug: Erasing the element shifts all the elements after that
        // If there are two consecutive dead entities, then the second one will
        // be skipped
        // for (size_t i = 0; i < entities.size();) {
        //     if (entities[i].health <= 0)
        //         entities.erase(entities.begin() + i);
        //     else // This is the fix
        //         i++;
        // }

        // A faster way to cleanup
        entities.erase(
            std::remove_if(
                entities.begin(),
                entities.end(),
                [](const Entity& e) { return e.health <= 0.0f; }
            ),
            entities.end()
        );
    }

    const Entity* FindByName(const std::string& name) {
        for (auto& e : entities)
            if (e.name == name)
                return &e;
        return nullptr;
    }

    float AverageHealth() const {
        if (entities.empty())
            return 0.0f;
        float total = 0;
        for (const auto& e : entities)
            total += e.health;
        // Bug: might be minor but this is int division and it truncates, so
        // precision is lost
        // Bug: Possible division by 0
        return total / entities.size();
    }

    void Print() const {
        // I think this will take forever if the number of entities are even a
        // couple hundred I'd use the equivalent of StringBuilder in C# and
        // print it at once
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

    // Bug: Dangling pointer here, should get troll after cleanup
    // const Entity* troll = w.FindByName("troll");

    w.Explode(0.f, 0.f, 3.f, 40.f);
    w.Cleanup();

    const Entity* troll = w.FindByName("troll");

    w.Print();

    printf("troll health: %.1f\n", troll->health);
    printf("average: %.1f\n", w.AverageHealth());
}