#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "Window.h"
#include "Clock.h"
#include "../rendering/Renderer.h"
#include "../physics/PhysicsEngine.h"
#include "../input/InputManager.h"
#include "../world/World.h"
#include "../../game/GameState.h"

namespace OpenHorizon {

class Engine {
public:
    Engine();
    ~Engine();

    void initialize(int width, int height, const char* title);
    void run();
    void shutdown();

    bool isRunning() const { return running_; }
    float getDeltaTime() const { return clock_->getDeltaTime(); }
    
    Window* getWindow() { return window_.get(); }
    Renderer* getRenderer() { return renderer_.get(); }
    PhysicsEngine* getPhysics() { return physicsEngine_.get(); }
    InputManager* getInput() { return inputManager_.get(); }
    World* getWorld() { return world_.get(); }
    GameState* getGameState() { return gameState_.get(); }

private:
    void update(float deltaTime);
    void render();

    bool running_;
    std::unique_ptr<Window> window_;
    std::unique_ptr<Clock> clock_;
    std::unique_ptr<Renderer> renderer_;
    std::unique_ptr<PhysicsEngine> physicsEngine_;
    std::unique_ptr<InputManager> inputManager_;
    std::unique_ptr<World> world_;
    std::unique_ptr<GameState> gameState_;
};

} // namespace OpenHorizon
