#include "game/RaceManager.h"
#include "engine/physics/Vehicle.h"
#include <algorithm>

namespace OpenHorizon {

RaceManager::RaceManager()
    : isRaceActive_(false),
      raceStartTime_(0.0f),
      currentLapTime_(0.0f),
      currentCheckpoint_(0) {}

void RaceManager::startRace(const std::vector<std::shared_ptr<Vehicle>>& participants) {
    isRaceActive_ = true;
    raceStartTime_ = 0.0f;
    currentLapTime_ = 0.0f;
    currentCheckpoint_ = 0;
    results_.clear();
    
    // Setup checkpoints
    checkpoints_.clear();
    checkpoints_.push_back({glm::vec3(0.0f, 0.0f, 0.0f), 20.0f, 0});
    checkpoints_.push_back({glm::vec3(100.0f, 0.0f, 100.0f), 20.0f, 1});
    checkpoints_.push_back({glm::vec3(-100.0f, 0.0f, 100.0f), 20.0f, 2});
}

void RaceManager::update(float deltaTime) {
    if (!isRaceActive_) return;
    raceStartTime_ += deltaTime;
    currentLapTime_ += deltaTime;
}

void RaceManager::endRace() {
    isRaceActive_ = false;
}

bool RaceManager::checkpointReached(const glm::vec3& position) {
    if (currentCheckpoint_ >= checkpoints_.size()) return false;
    
    const Checkpoint& cp = checkpoints_[currentCheckpoint_];
    if (glm::distance(position, cp.position) < cp.radius) {
        currentCheckpoint_++;
        return true;
    }
    return false;
}

} // namespace OpenHorizon
