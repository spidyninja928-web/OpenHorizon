#include "engine/world/World.h"
#include "Terrain.h"
#include "../physics/Vehicle.h"
#include "../physics/PhysicsEngine.h"
#include "../rendering/Renderer.h"

namespace OpenHorizon {

World::World(PhysicsEngine* physics)
    : physics_(physics) {}

World::~World() = default;

void World::initialize() {
    terrain_ = std::make_unique<Terrain>(256, 1.0f);
    terrain_->generate();
    generateRoadNetwork();
    generateScenery();
}

void World::update(float deltaTime) {
    if (terrain_) {
        terrain_->update();
    }
}

void World::render(Renderer* renderer) {
    if (terrain_ && renderer) {
        renderer->drawTerrain(terrain_.get());
    }
}

void World::addVehicle(std::shared_ptr<Vehicle> vehicle) {
    if (vehicle && physics_) {
        vehicles_.push_back(vehicle);
        physics_->addVehicle(vehicle);
    }
}

void World::spawnAIVehicles(int count) {
    for (int i = 0; i < count; ++i) {
        VehicleSpec spec;
        spec.name = "AI_Vehicle_" + std::to_string(i);
        spec.mass = 1500.0f;
        spec.topSpeed = 250.0f;
        spec.acceleration = 150.0f;
        spec.braking = 200.0f;
        spec.handling = 0.85f;
        
        auto vehicle = std::make_shared<Vehicle>(spec);
        addVehicle(vehicle);
    }
}

void World::generateRoadNetwork() {
    // Generate procedural road network
    roadNodes_.push_back(glm::vec3(0.0f, 0.0f, -100.0f));
    roadNodes_.push_back(glm::vec3(100.0f, 0.0f, 0.0f));
    roadNodes_.push_back(glm::vec3(0.0f, 0.0f, 100.0f));
    roadNodes_.push_back(glm::vec3(-100.0f, 0.0f, 0.0f));
}

void World::generateScenery() {
    // Generate buildings, trees, and other scenery
}

} // namespace OpenHorizon
