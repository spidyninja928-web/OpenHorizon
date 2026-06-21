#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>

namespace OpenHorizon {

class Terrain;
class Vehicle;
class PhysicsEngine;
class Renderer;

class World {
public:
    World(PhysicsEngine* physics);
    ~World();

    void initialize();
    void update(float deltaTime);
    void render(Renderer* renderer);
    
    Terrain* getTerrain() { return terrain_.get(); }
    const std::vector<std::shared_ptr<Vehicle>>& getVehicles() const { return vehicles_; }
    
    void addVehicle(std::shared_ptr<Vehicle> vehicle);
    void spawnAIVehicles(int count);

private:
    void generateRoadNetwork();
    void generateScenery();

    PhysicsEngine* physics_;
    std::unique_ptr<Terrain> terrain_;
    std::vector<std::shared_ptr<Vehicle>> vehicles_;
    std::vector<glm::vec3> roadNodes_;
};

} // namespace OpenHorizon
