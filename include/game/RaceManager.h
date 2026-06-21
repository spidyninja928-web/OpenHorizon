#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <memory>

namespace OpenHorizon {

struct Checkpoint {
    glm::vec3 position;
    float radius;
    int index;
};

struct RaceResult {
    std::string playerName;
    float time;
    int position;
    float bestLapTime;
};

class Vehicle;

class RaceManager {
public:
    RaceManager();
    
    void startRace(const std::vector<std::shared_ptr<Vehicle>>& participants);
    void update(float deltaTime);
    void endRace();
    
    bool checkpointReached(const glm::vec3& position);
    const std::vector<RaceResult>& getResults() const { return results_; }
    
    float getCurrentLapTime() const { return currentLapTime_; }
    int getCurrentCheckpoint() const { return currentCheckpoint_; }
    bool isRaceActive() const { return isRaceActive_; }

private:
    std::vector<Checkpoint> checkpoints_;
    std::vector<RaceResult> results_;
    
    bool isRaceActive_;
    float raceStartTime_;
    float currentLapTime_;
    int currentCheckpoint_;
};

} // namespace OpenHorizon
