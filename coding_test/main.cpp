#include <cstdio>
#include <string>
#include <unordered_map>
#include <vector>

namespace original {
struct Voice {
    std::string sound_;
    float volume_;
    float time_left_;
    bool active_;
};

class Mixer {
  public:
    explicit Mixer(int max_voices) : voices_(max_voices) {}

    // Starts a sound. Returns a pointer so game code can adjust it later.
    Voice* play(const std::string& sound, float volume, float duration) {
        for (auto& v : voices_) {
            if (!v.active_) {
                v = {sound, volume, duration, true};
                return &v;
            }
        }
        // TODO: when all voices are busy, steal the quietest one instead.
        return nullptr;
    }

    void update(float dt) {
        for (auto& v : voices_) {
            if (v.active_) {
                v.time_left_ -= dt;
                if (v.time_left_ <= 0.f)
                    v.active_ = false;
            }
        }
    }

    int active_count() const {
        int n = 0;
        for (auto v : voices_)
            if (v.active_)
                n++;
        return n;
    }

    void print() const {
        for (const auto& v : voices_)
            if (v.active_)
                printf(
                    "  %s vol=%.2f left=%.2f\n",
                    v.sound_.c_str(),
                    v.volume_,
                    v.time_left_
                );
    }

  private:
    std::vector<Voice> voices_;
};

void run() {
    Mixer mixer(3);

    Voice* music = mixer.play("music", 0.5f, 100.f);
    Voice* footstep = mixer.play("footstep", 0.2f, 0.3f);
    Voice* gunshot = mixer.play("gunshot", 0.9f, 1.0f);
    Voice* boom = mixer.play("explosion", 1.0f, 2.0f); // all voices busy

    // Later, game code adjusts the sounds it started.
    footstep->volume_ = 0.05f;
    if (boom)
        boom->time_left_ += 0.5f;

    mixer.update(0.5f);

    printf("active: %d\n", mixer.active_count());
    mixer.print();
    (void)music;
    (void)gunshot;
}
} // namespace original

namespace improved {
struct Voice {
    std::string sound_;
    float volume_;
    float time_left_;
    bool active_;
};

class Mixer {
  public:
    explicit Mixer(int max_voices) : max_voices_(max_voices) {}

    // Starts a sound. Returns a pointer so game code can adjust it later.
    int play(const std::string& sound, float volume, float duration) {
        if (id_to_voice_.size() < max_voices_) {
            Voice v = {sound, volume, duration, true};
            id_to_voice_[++playing_id_counter_] = v;
        } else {
            float min_volume = 1.0f;
            int current_key = -1;
            for (auto& [k, v] : id_to_voice_) {
                if (v.volume_ <= min_volume) {
                    min_volume = v.volume_;
                    current_key = k;
                }
            }

            id_to_voice_.erase(current_key);
            Voice v = {sound, volume, duration, true};
            id_to_voice_[++playing_id_counter_] = v;
        }

        return playing_id_counter_;
    }

    void update(float dt) {
        for (auto& [id, v] : id_to_voice_) {
            if (v.active_) {
                v.time_left_ -= dt;
                if (v.time_left_ <= 0.f)
                    v.active_ = false;
            }
        }
    }

    void set_volume(int playing_id, float volume) {
        if (id_to_voice_.contains(playing_id)) {
            id_to_voice_[playing_id].volume_ = volume;
        }
    }

    void add_time_left(int playing_id, float time_left) {
        if (id_to_voice_.contains(playing_id)) {
            id_to_voice_[playing_id].time_left_ += time_left;
        }
    }

    int active_count() const {
        int n = 0;
        // Added &, so the voices are not copied
        for (const auto& [id, v] : id_to_voice_)
            if (v.active_)
                n++;
        return n;
    }

    void print() const {
        for (const auto& [id, v] : id_to_voice_)
            if (v.active_)
                printf(
                    "  %s vol=%.2f left=%.2f\n",
                    v.sound_.c_str(),
                    v.volume_,
                    v.time_left_
                );
    }

  private:
    std::unordered_map<int, Voice> id_to_voice_;
    int max_voices_ = 0;
    int playing_id_counter_ = 0;
};

void run() {
    Mixer mixer(3);

    int music_id = mixer.play("music", 0.5f, 100.f);
    int footstep_id = mixer.play("footstep", 0.2f, 0.3f);
    int gunshot_id = mixer.play("gunshot", 0.9f, 1.0f);
    // This one invalidates the footstep pointer, this one reminds our design
    // We returned an id instead of a pointer to alter the voices after playing
    int boom_id = mixer.play("explosion", 1.0f, 2.0f); // all voices busy

    // Later, game code adjusts the sounds it started.
    mixer.set_volume(footstep_id, 0.05f);
    if (boom_id != -1) {
        mixer.add_time_left(boom_id, 0.5f);
    }

    mixer.update(0.5f);

    printf("active: %d\n", mixer.active_count());
    mixer.print();
    // (void)music;
    // (void)gunshot;
}
} // namespace improved

int main() {
    original::run();
    improved::run();
}

/*
Implements a audio mixer class to play sounds.
Creates a mixer with max 3 sound and then plays 4 sounds.
*/