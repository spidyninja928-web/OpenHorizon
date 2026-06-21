#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>

namespace OpenHorizon {

class Mesh;

class Terrain {
public:
    Terrain(int gridSize, float scale);
    ~Terrain();

    void generate();
    void update();
    
    float getHeightAt(float x, float z) const;
    glm::vec3 getNormalAt(float x, float z) const;
    
    const Mesh* getMesh() const { return mesh_.get(); }
    int getGridSize() const { return gridSize_; }
    float getScale() const { return scale_; }

private:
    float perlinNoise(float x, float y) const;
    void generateHeightmap();
    void generateMesh();

    int gridSize_;
    float scale_;
    std::vector<float> heightmap_;
    std::unique_ptr<Mesh> mesh_;
};

} // namespace OpenHorizon
