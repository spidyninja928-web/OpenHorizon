#include "engine/core/Window.h"
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <stdexcept>
#include <iostream>

namespace OpenHorizon {

Window::Window() : window_(nullptr), width_(0), height_(0) {}

Window::~Window() {
    destroy();
}

void Window::create(int width, int height, const std::string& title) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window_) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    
    width_ = width;
    height_ = height;
    
    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1); // Enable V-sync
    
    if (glewInit() != GLEW_OK) {
        glfwDestroyWindow(window_);
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLEW");
    }
    
    // Setup callbacks
    glfwSetWindowUserPointer(window_, this);
    glfwSetWindowSizeCallback(window_, resizeCallback);
    glfwSetKeyCallback(window_, keyCallback);
    glfwSetCursorPosCallback(window_, mouseMoveCallback);
    glfwSetMouseButtonCallback(window_, mouseClickCallback);
    
    std::cout << "Window created: " << width << "x" << height << std::endl;
}

void Window::destroy() {
    if (window_) {
        glfwDestroyWindow(window_);
        glfwTerminate();
        window_ = nullptr;
    }
}

void Window::swapBuffers() {
    glfwSwapBuffers(window_);
    glfwPollEvents();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window_);
}

void Window::setShouldClose(bool close) {
    glfwSetWindowShouldClose(window_, close);
}

void Window::resizeCallback(GLFWwindow* window, int width, int height) {
    Window* pThis = static_cast<Window*>(glfwGetWindowUserPointer(window));
    pThis->width_ = width;
    pThis->height_ = height;
    if (pThis->onWindowResized) pThis->onWindowResized(width, height);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Window* pThis = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (pThis->onKey) pThis->onKey(key, action, mods);
}

void Window::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos) {
    Window* pThis = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (pThis->onMouseMove) pThis->onMouseMove(xpos, ypos);
}

void Window::mouseClickCallback(GLFWwindow* window, int button, int action, int mods) {
    Window* pThis = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (pThis->onMouseClick) pThis->onMouseClick(button, action);
}

} // namespace OpenHorizon
