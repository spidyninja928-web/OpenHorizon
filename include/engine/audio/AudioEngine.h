#pragma once

#include <string>
#include <memory>
#include <unordered_map>

namespace OpenHorizon {

class AudioSource;

class AudioEngine {
public:
    AudioEngine();
    ~AudioEngine();

    void initialize();
    void update(float deltaTime);
    
    void playSound(const std::string& soundName, float volume = 1.0f);
    void playMusic(const std::string& musicName, bool loop = true);
    void stopMusic();
    
    void setMasterVolume(float volume);
    void setEngineSound(float rpm, float throttle, int gear);
    void setDriftSound(bool drifting, float intensity);

private:
    std::unordered_map<std::string, std::shared_ptr<AudioSource>> soundLibrary_;
    std::shared_ptr<AudioSource> currentMusic_;
    float masterVolume_;
};

} // namespace OpenHorizon
