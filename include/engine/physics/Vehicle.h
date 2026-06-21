#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <array>
#include <string>

namespace OpenHorizon {

struct VehicleSpec {
    std::string name;
    float mass;
    float topSpeed;
    float acceleration;
    float braking;
    float handling;
    float weight;
    glm::vec3 centerOfMass;
    glm::vec3 dimensions;
    float wheelRadius;
    float rpmMax;
};

class Vehicle {
public:
    Vehicle(const VehicleSpec& spec);
    ~Vehicle();

    void update(float deltaTime);
    void applyInput(float throttle, float brake, float steering, bool handbrake, bool nitro);
    
    // Getters
    const glm::vec3& getPosition() const { return position_; }
    const glm::vec3& getVelocity() const { return velocity_; }
    float getSpeed() const;
    float getHeading() const { return heading_; }
    int getCurrentGear() const { return currentGear_; }
    float getRPM() const { return rpm_; }
    float getNitroLevel() const { return nitroLevel_; }
    bool isDrifting() const { return isDrifting_; }
    
    // Setters
    void setPosition(const glm::vec3& pos) { position_ = pos; }
    void setHeading(float h) { heading_ = h; }
    void reset();

private:
    void calculateEngineForce(float deltaTime);
    void calculateDrag();
    void updateGear();
    void applyDrift(float deltaTime);
    void applyNitro(float deltaTime);

    // Spec
    VehicleSpec spec_;

    // Physics state
    glm::vec3 position_;
    glm::vec3 velocity_;
    glm::vec3 acceleration_;
    float heading_;
    float steerAngle_;
    float driftAngle_;
    
    // Engine
    float rpm_;
    int currentGear_;
    float throttle_;
    float brakeForce_;
    float wheelRotation_;
    
    // Nitro
    float nitroLevel_;
    float nitroConsumption_;
    
    // Drift
    bool isDrifting_;
    float driftTimer_;
    float driftScore_;
    
    // Suspension
    std::array<float, 4> suspensionCompression_;
};

} // namespace OpenHorizon
