#pragma once

#include <string>
#include <functional>

struct GLFWwindow;

namespace OpenHorizon {

class Window {
public:
    Window();
    ~Window();

    void create(int width, int height, const std::string& title);
    void destroy();
    void swapBuffers();
    bool shouldClose() const;
    void setShouldClose(bool close);

    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    float getAspectRatio() const { return static_cast<float>(width_) / height_; }
    GLFWwindow* getHandle() { return window_; }

    // Callbacks
    std::function<void(int, int)> onWindowResized;
    std::function<void(int, int, int)> onKey;
    std::function<void(double, double)> onMouseMove;
    std::function<void(int, int)> onMouseClick;

private:
    static void resizeCallback(GLFWwindow* window, int width, int height);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
    static void mouseClickCallback(GLFWwindow* window, int button, int action, int mods);

    GLFWwindow* window_;
    int width_, height_;
};

} // namespace OpenHorizon
