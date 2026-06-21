#include "engine/rendering/Renderer.h"
#include <GL/glew.h>
#include <iostream>

namespace OpenHorizon {

Renderer::Renderer() 
    : windowWidth_(1920), 
      windowHeight_(1080),
      shadowFramebuffer_(0),
      shadowMap_(0) {}

Renderer::~Renderer() = default;

void Renderer::initialize(int width, int height) {
    windowWidth_ = width;
    windowHeight_ = height;
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    std::cout << "Renderer initialized with resolution: " << width << "x" << height << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GPU: " << glGetString(GL_RENDERER) << std::endl;
}

void Renderer::beginFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::endFrame() {
    glFlush();
}

void Renderer::setViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}

void Renderer::clear(const glm::vec4& color) {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawMesh(const Mesh* mesh, const glm::mat4& transform, const Shader* shader) {
    // Mesh drawing implementation
}

void Renderer::drawTerrain(const class Terrain* terrain) {
    // Terrain rendering implementation
}

void Renderer::renderShadowMap() {
    // Shadow map rendering
}

void Renderer::applyMotionBlur(float intensity) {
    // Post-process: motion blur
}

void Renderer::applyChromaticAberration(float intensity) {
    // Post-process: chromatic aberration
}

void Renderer::applyVignette(float intensity) {
    // Post-process: vignette
}

} // namespace OpenHorizon
