#include "game/GameState.h"
#include "engine/physics/Vehicle.h"
#include "engine/rendering/Renderer.h"
#include "engine/physics/PhysicsEngine.h"
#include "engine/input/InputManager.h"
#include <cmath>

namespace OpenHorizon {

GameState::GameState(Renderer* renderer, PhysicsEngine* physics)
    : renderer_(renderer),
      physics_(physics),
      currentMode_(GameMode::FREEROAM),
      gameTime_(0.0f),
      weatherIntensity_(0.5f),
      isPaused_(false),
      currentCameraMode_(0) {}

GameState::~GameState() = default;

void GameState::update(float deltaTime, const InputState& input) {
    gameTime_ += deltaTime;
    
    switch (currentMode_) {
        case GameMode::FREEROAM:
            updateFreeroam(deltaTime, input);
            break;
        case GameMode::RACE:
            updateRace(deltaTime, input);
            break;
        case GameMode::PAUSE:
            // Pause logic
            break;
        default:
            break;
    }
    
    handleInput(deltaTime, input);
    updateCamera(deltaTime);
}

void GameState::render() {
    // Render game UI and HUD
}

void GameState::setGameMode(GameMode mode) {
    currentMode_ = mode;
}

void GameState::selectVehicle(const std::string& vehicleName) {
    VehicleSpec spec;
    spec.name = vehicleName;
    spec.mass = 1500.0f;
    spec.topSpeed = 280.0f;
    spec.acceleration = 200.0f;
    spec.braking = 250.0f;
    spec.handling = 0.9f;
    spec.rpmMax = 7500.0f;
    spec.wheelRadius = 0.35f;
    spec.dimensions = glm::vec3(2.0f, 1.3f, 4.5f);
    
    playerVehicle_ = std::make_shared<Vehicle>(spec);
    if (physics_) {
        physics_->addVehicle(playerVehicle_);
    }
}

float GameState::getDayNightCycle() const {
    // Cycle from 0 (day) to 1 (night) and back
    return 0.5f + 0.5f * std::sin(gameTime_ * 0.0001f);
}

void GameState::updateFreeroam(float deltaTime, const InputState& input) {
    if (!playerVehicle_) return;
    
    playerVehicle_->applyInput(
        input.throttle,
        input.brake,
        input.steering,
        input.handbrake,
        input.nitro
    );
}

void GameState::updateRace(float deltaTime, const InputState& input) {
    updateFreeroam(deltaTime, input);
    // Additional race-specific logic
}

void GameState::handleInput(float deltaTime, const InputState& input) {
    if (input.pause) {
        isPaused_ = !isPaused_;
    }
    if (input.cameraChange) {
        currentCameraMode_ = (currentCameraMode_ + 1) % 3;
    }
}

void GameState::updateCamera(float deltaTime) {
    // Camera updates handled separately
}

} // namespace OpenHorizon
