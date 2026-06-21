#include "engine/physics/Vehicle.h"
#include <cmath>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

namespace OpenHorizon {

Vehicle::Vehicle(const VehicleSpec& spec)
    : spec_(spec),
      position_(0.0f),
      velocity_(0.0f),
      acceleration_(0.0f),
      heading_(0.0f),
      steerAngle_(0.0f),
      driftAngle_(0.0f),
      rpm_(0.0f),
      currentGear_(0),
      throttle_(0.0f),
      brakeForce_(0.0f),
      wheelRotation_(0.0f),
      nitroLevel_(100.0f),
      nitroConsumption_(30.0f),
      isDrifting_(false),
      driftTimer_(0.0f),
      driftScore_(0.0f) {
    suspensionCompression_.fill(0.0f);
}

Vehicle::~Vehicle() = default;

void Vehicle::update(float deltaTime) {
    // Update engine
    calculateEngineForce(deltaTime);
    calculateDrag();
    updateGear();
    
    // Drift mechanics
    applyDrift(deltaTime);
    applyNitro(deltaTime);
    
    // Position update
    float moveHeading = heading_ + driftAngle_ * 0.5f;
    float speed = glm::length(velocity_);
    
    position_.x += std::sin(moveHeading) * speed * deltaTime;
    position_.z += std::cos(moveHeading) * speed * deltaTime;
    
    // Wheel rotation
    if (speed > 0.1f) {
        wheelRotation_ += (speed / spec_.wheelRadius) * deltaTime;
    }
}

void Vehicle::applyInput(float throttle, float brake, float steering, bool handbrake, bool nitro) {
    throttle_ = std::clamp(throttle, -1.0f, 1.0f);
    brakeForce_ = std::clamp(brake, 0.0f, 1.0f);
    steerAngle_ = std::clamp(steering, -1.0f, 1.0f) * 0.5f;
    
    if (nitro && nitroLevel_ > 0.0f) {
        nitroLevel_ = std::max(0.0f, nitroLevel_ - nitroConsumption_);
    } else {
        nitroLevel_ = std::min(100.0f, nitroLevel_ + 15.0f);
    }
    
    // Handbrake drift
    if (handbrake) {
        isDrifting_ = true;
        driftTimer_ += 0.016f;
    }
}

float Vehicle::getSpeed() const {
    return glm::length(velocity_) * 3.6f; // Convert to km/h
}

void Vehicle::calculateEngineForce(float deltaTime) {
    float force = 0.0f;
    
    if (throttle_ > 0.0f) {
        force = spec_.acceleration * throttle_ * (1.0f - (glm::length(velocity_) / spec_.topSpeed) * 0.9f);
    } else if (brakeForce_ > 0.0f) {
        force = -spec_.braking * brakeForce_;
    }
    
    velocity_.x += force * std::sin(heading_) * deltaTime;
    velocity_.z += force * std::cos(heading_) * deltaTime;
    
    // Rotation from steering
    float rotationSpeed = steerAngle_ * spec_.handling * (glm::length(velocity_) / spec_.topSpeed) * deltaTime;
    heading_ += rotationSpeed;
}

void Vehicle::calculateDrag() {
    float speed = glm::length(velocity_);
    float dragForce = speed * speed * 0.01f; // Quadratic drag
    
    if (speed > 0.1f) {
        velocity_ *= (1.0f - dragForce * 0.016f); // Approximate timestep
    }
}

void Vehicle::updateGear() {
    float speed = glm::length(velocity_) * 3.6f;
    
    if (speed < 10.0f) currentGear_ = 1;
    else if (speed < 25.0f) currentGear_ = 2;
    else if (speed < 40.0f) currentGear_ = 3;
    else if (speed < 60.0f) currentGear_ = 4;
    else if (speed < 80.0f) currentGear_ = 5;
    else currentGear_ = 6;
    
    rpm_ = (speed / (currentGear_ * 15.0f)) * spec_.rpmMax;
}

void Vehicle::applyDrift(float deltaTime) {
    if (isDrifting_ && driftTimer_ > 0.0f) {
        driftAngle_ = steerAngle_ * 2.5f;
        driftScore_ += 1.0f;
    } else {
        isDrifting_ = false;
        driftAngle_ *= 0.95f;
        driftTimer_ = 0.0f;
    }
}

void Vehicle::applyNitro(float deltaTime) {
    // Nitro boost handled in input
}

void Vehicle::reset() {
    position_ = glm::vec3(0.0f);
    velocity_ = glm::vec3(0.0f);
    acceleration_ = glm::vec3(0.0f);
    heading_ = 0.0f;
    steerAngle_ = 0.0f;
    driftAngle_ = 0.0f;
    rpm_ = 0.0f;
    currentGear_ = 0;
    throttle_ = 0.0f;
    brakeForce_ = 0.0f;
    nitroLevel_ = 100.0f;
    driftScore_ = 0.0f;
}

} // namespace OpenHorizon
