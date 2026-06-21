#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <string>

namespace OpenHorizon {

class Mesh;
class Shader;
class Texture;
class Camera;

struct RenderStats {
    unsigned int verticesDrawn;
    unsigned int trianglesDrawn;
    unsigned int drawCalls;
    float gpuMemoryMB;
};

class Renderer {
public:
    Renderer();
    ~Renderer();

    void initialize(int width, int height);
    void beginFrame();
    void endFrame();
    void setViewport(int x, int y, int width, int height);
    void clear(const glm::vec4& color);
    
    void drawMesh(const Mesh* mesh, const glm::mat4& transform, const Shader* shader);
    void drawTerrain(const class Terrain* terrain);
    
    // Shadows
    void renderShadowMap();
    
    // Post-processing
    void applyMotionBlur(float intensity);
    void applyChromaticAberration(float intensity);
    void applyVignette(float intensity);
    
    const RenderStats& getStats() const { return stats_; }
    void resetStats() { stats_ = {}; }

private:
    RenderStats stats_;
    int windowWidth_, windowHeight_;
    unsigned int shadowFramebuffer_;
    unsigned int shadowMap_;
};

} // namespace OpenHorizon
