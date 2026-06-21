#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "Vehicle.h"

class btDynamicsWorld;
class btBroadphaseInterface;
class btCollisionConfiguration;
class btConstraintSolver;
class btCollisionDispatcher;

namespace OpenHorizon {

class PhysicsEngine {
public:
    PhysicsEngine();
    ~PhysicsEngine();

    void initialize();
    void update(float deltaTime);
    void addVehicle(std::shared_ptr<Vehicle> vehicle);
    
    // Raycasting for terrain
    float getTerrainHeight(float x, float z) const;
    glm::vec3 getTerrainNormal(float x, float z) const;
    
    // Collision detection
    bool checkCollision(const glm::vec3& pos1, const glm::vec3& pos2, float radius) const;

private:
    std::unique_ptr<btBroadphaseInterface> broadphase_;
    std::unique_ptr<btCollisionConfiguration> collisionConfig_;
    std::unique_ptr<btCollisionDispatcher> dispatcher_;
    std::unique_ptr<btConstraintSolver> solver_;
    std::unique_ptr<btDynamicsWorld> world_;
    
    std::vector<std::shared_ptr<Vehicle>> vehicles_;
};

} // namespace OpenHorizon
