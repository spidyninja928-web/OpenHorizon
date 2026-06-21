#include "engine/input/InputManager.h"
#include <GLFW/glfw3.h>
#include <cstring>

namespace OpenHorizon {

InputManager::InputManager() : mouseX_(0.0), mouseY_(0.0) {
    std::memset(keyStates_, 0, sizeof(keyStates_));
    std::memset(previousKeyStates_, 0, sizeof(previousKeyStates_));
}

InputManager::~InputManager() = default;

void InputManager::update() {
    previousState_ = state_;
    std::memcpy(previousKeyStates_, keyStates_, sizeof(keyStates_));
    
    // Update analog inputs
    state_.throttle = 0.0f;
    state_.brake = 0.0f;
    state_.steering = 0.0f;
    
    if (isKeyPressed(GLFW_KEY_W) || isKeyPressed(GLFW_KEY_UP)) state_.throttle = 1.0f;
    if (isKeyPressed(GLFW_KEY_S) || isKeyPressed(GLFW_KEY_DOWN)) state_.brake = 1.0f;
    if (isKeyPressed(GLFW_KEY_A) || isKeyPressed(GLFW_KEY_LEFT)) state_.steering = -1.0f;
    if (isKeyPressed(GLFW_KEY_D) || isKeyPressed(GLFW_KEY_RIGHT)) state_.steering = 1.0f;
    
    state_.handbrake = isKeyPressed(GLFW_KEY_SPACE);
    state_.nitro = isKeyPressed(GLFW_KEY_LEFT_SHIFT) || isKeyPressed(GLFW_KEY_RIGHT_SHIFT);
    state_.pause = isKeyJustPressed(GLFW_KEY_ESCAPE);
    state_.cameraChange = isKeyJustPressed(GLFW_KEY_C);
}

bool InputManager::isKeyPressed(int key) const {
    return keyStates_[key];
}

bool InputManager::isKeyJustPressed(int key) const {
    return keyStates_[key] && !previousKeyStates_[key];
}

void InputManager::onKey(int key, int action) {
    if (action == GLFW_PRESS) {
        keyStates_[key] = true;
    } else if (action == GLFW_RELEASE) {
        keyStates_[key] = false;
    }
}

void InputManager::onMouseMove(double x, double y) {
    mouseX_ = x;
    mouseY_ = y;
}

} // namespace OpenHorizon
