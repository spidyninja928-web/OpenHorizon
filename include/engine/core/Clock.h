#pragma once

namespace OpenHorizon {

class Clock {
public:
    Clock();
    void tick();
    float getDeltaTime() const { return deltaTime_; }
    double getTotalTime() const { return totalTime_; }
    unsigned long getFrameCount() const { return frameCount_; }
    float getFPS() const { return fps_; }

private:
    double lastTime_;
    double totalTime_;
    float deltaTime_;
    float fps_;
    unsigned long frameCount_;
    double fpsUpdateTime_;
};

} // namespace OpenHorizon
