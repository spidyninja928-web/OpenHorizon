#pragma once

#include <memory>
#include <glm/glm.hpp>

namespace OpenHorizon {

class Vehicle;
class Renderer;
class PhysicsEngine;

struct InputState;

enum class GameMode {
    FREEROAM,
    RACE,
    CHAMPIONSHIP,
    MULTIPLAYER,
    PAUSE,
    MENU
};

class GameState {
public:
    GameState(Renderer* renderer, PhysicsEngine* physics);
    ~GameState();

    void update(float deltaTime, const InputState& input);
    void render();
    
    GameMode getCurrentMode() const { return currentMode_; }
    void setGameMode(GameMode mode);
    
    Vehicle* getPlayerVehicle() { return playerVehicle_.get(); }
    void selectVehicle(const std::string& vehicleName);
    
    float getGameTime() const { return gameTime_; }
    float getDayNightCycle() const;
    
    // Weather
    float getWeatherIntensity() const { return weatherIntensity_; }
    void setWeatherIntensity(float intensity) { weatherIntensity_ = intensity; }

private:
    void updateFreeroam(float deltaTime, const InputState& input);
    void updateRace(float deltaTime, const InputState& input);
    void handleInput(float deltaTime, const InputState& input);
    void updateCamera(float deltaTime);

    Renderer* renderer_;
    PhysicsEngine* physics_;
    
    GameMode currentMode_;
    std::shared_ptr<Vehicle> playerVehicle_;
    
    float gameTime_;
    float weatherIntensity_;
    bool isPaused_;
    int currentCameraMode_;
};

} // namespace OpenHorizon
