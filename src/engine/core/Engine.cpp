#include "engine/core/Engine.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace OpenHorizon {

Engine::Engine() : running_(false) {}

Engine::~Engine() = default;

void Engine::initialize(int width, int height, const char* title) {
    std::cout << "Initializing OpenHorizon Engine..." << std::endl;
    
    // Initialize window
    window_ = std::make_unique<Window>();
    window_->create(width, height, title);
    
    // Initialize clock
    clock_ = std::make_unique<Clock>();
    
    // Initialize renderer
    renderer_ = std::make_unique<Renderer>();
    renderer_->initialize(width, height);
    
    // Initialize physics
    physicsEngine_ = std::make_unique<PhysicsEngine>();
    physicsEngine_->initialize();
    
    // Initialize input
    inputManager_ = std::make_unique<InputManager>();
    
    // Initialize world
    world_ = std::make_unique<World>(physicsEngine_.get());
    world_->initialize();
    
    // Initialize game state
    gameState_ = std::make_unique<GameState>(renderer_.get(), physicsEngine_.get());
    gameState_->setGameMode(GameMode::FREEROAM);
    
    running_ = true;
    std::cout << "Engine initialized successfully!" << std::endl;
}

void Engine::run() {
    while (running_ && !window_->shouldClose()) {
        clock_->tick();
        float deltaTime = clock_->getDeltaTime();
        
        // Update
        inputManager_->update();
        physicsEngine_->update(deltaTime);
        gameState_->update(deltaTime, inputManager_->getState());
        world_->update(deltaTime);
        
        // Render
        renderer_->beginFrame();
        renderer_->clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        
        world_->render(renderer_.get());
        gameState_->render();
        
        renderer_->endFrame();
        window_->swapBuffers();
    }
}

void Engine::shutdown() {
    std::cout << "Shutting down engine..." << std::endl;
    window_->destroy();
}

} // namespace OpenHorizon
