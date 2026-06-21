#include "engine/physics/PhysicsEngine.h"
#include <glm/glm.hpp>

namespace OpenHorizon {

PhysicsEngine::PhysicsEngine() = default;

PhysicsEngine::~PhysicsEngine() = default;

void PhysicsEngine::initialize() {
    // Bullet physics initialization would go here
}

void PhysicsEngine::update(float deltaTime) {
    for (auto& vehicle : vehicles_) {
        if (vehicle) {
            vehicle->update(deltaTime);
        }
    }
}

void PhysicsEngine::addVehicle(std::shared_ptr<Vehicle> vehicle) {
    if (vehicle) {
        vehicles_.push_back(vehicle);
    }
}

float PhysicsEngine::getTerrainHeight(float x, float z) const {
    // Procedural height calculation
    return 10.0f + std::sin(x * 0.01f) * 5.0f + std::cos(z * 0.01f) * 3.0f;
}

glm::vec3 PhysicsEngine::getTerrainNormal(float x, float z) const {
    return glm::normalize(glm::vec3(std::sin(x * 0.01f), 1.0f, std::cos(z * 0.01f)));
}

bool PhysicsEngine::checkCollision(const glm::vec3& pos1, const glm::vec3& pos2, float radius) const {
    float dist = glm::distance(pos1, pos2);
    return dist < radius * 2.0f;
}

} // namespace OpenHorizon
