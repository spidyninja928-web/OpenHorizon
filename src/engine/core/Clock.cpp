#include "engine/core/Clock.h"
#include <GLFW/glfw3.h>
#include <algorithm>

namespace OpenHorizon {

Clock::Clock() 
    : lastTime_(glfwGetTime()), 
      totalTime_(0.0), 
      deltaTime_(0.0f), 
      fps_(0.0f), 
      frameCount_(0),
      fpsUpdateTime_(0.0) {}

void Clock::tick() {
    double currentTime = glfwGetTime();
    deltaTime_ = static_cast<float>(currentTime - lastTime_);
    
    // Cap deltaTime to prevent large jumps
    deltaTime_ = std::min(deltaTime_, 0.033f); // Max 30ms
    
    lastTime_ = currentTime;
    totalTime_ += deltaTime_;
    frameCount_++;
    fpsUpdateTime_ += deltaTime_;
    
    if (fpsUpdateTime_ >= 1.0) {
        fps_ = frameCount_ / fpsUpdateTime_;
        frameCount_ = 0;
        fpsUpdateTime_ = 0.0;
    }
}

} // namespace OpenHorizon
