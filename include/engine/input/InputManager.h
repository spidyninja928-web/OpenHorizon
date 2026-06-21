#pragma once

#include <functional>
#include <glm/glm.hpp>

namespace OpenHorizon {

struct InputState {
    float throttle;      // -1 (reverse) to 1 (forward)
    float brake;         // 0 to 1
    float steering;      // -1 (left) to 1 (right)
    bool handbrake;
    bool nitro;
    bool pause;
    bool cameraChange;
};

class InputManager {
public:
    InputManager();
    ~InputManager();

    void update();
    const InputState& getState() const { return state_; }
    
    bool isKeyPressed(int key) const;
    bool isKeyJustPressed(int key) const;
    void onKey(int key, int action);
    void onMouseMove(double x, double y);

private:
    InputState state_;
    InputState previousState_;
    double mouseX_, mouseY_;
    bool keyStates_[512];
    bool previousKeyStates_[512];
};

} // namespace OpenHorizon
