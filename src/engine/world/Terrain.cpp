#include "engine/world/Terrain.h"
#include <cmath>
#include <random>

namespace OpenHorizon {

Terrain::Terrain(int gridSize, float scale)
    : gridSize_(gridSize), scale_(scale) {
    heightmap_.resize(gridSize * gridSize);
}

Terrain::~Terrain() = default;

void Terrain::generate() {
    generateHeightmap();
    generateMesh();
}

void Terrain::update() {
    // Terrain updates can go here
}

float Terrain::getHeightAt(float x, float z) const {
    // Sample heightmap with bilinear interpolation
    return 10.0f + perlinNoise(x * 0.01f, z * 0.01f) * 20.0f;
}

glm::vec3 Terrain::getNormalAt(float x, float z) const {
    float h1 = getHeightAt(x - 0.1f, z);
    float h2 = getHeightAt(x + 0.1f, z);
    float h3 = getHeightAt(x, z - 0.1f);
    float h4 = getHeightAt(x, z + 0.1f);
    
    glm::vec3 normal(
        (h1 - h2) * 5.0f,
        1.0f,
        (h3 - h4) * 5.0f
    );
    
    return glm::normalize(normal);
}

float Terrain::perlinNoise(float x, float y) const {
    // Simplified Perlin noise implementation
    return std::sin(x * 1.5f) * std::cos(y * 1.5f) + 
           std::sin(x * 3.0f) * std::cos(y * 3.0f) * 0.5f +
           std::sin(x * 6.0f) * std::cos(y * 6.0f) * 0.25f;
}

void Terrain::generateHeightmap() {
    for (int z = 0; z < gridSize_; ++z) {
        for (int x = 0; x < gridSize_; ++x) {
            int idx = z * gridSize_ + x;
            float fx = (x - gridSize_ / 2.0f) * scale_;
            float fz = (z - gridSize_ / 2.0f) * scale_;
            heightmap_[idx] = getHeightAt(fx, fz);
        }
    }
}

void Terrain::generateMesh() {
    // Mesh generation from heightmap
}

} // namespace OpenHorizon
