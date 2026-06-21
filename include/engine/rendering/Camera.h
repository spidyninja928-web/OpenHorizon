#pragma once

#include <glm/glm.hpp>

namespace OpenHorizon {

class Camera {
public:
    Camera();
    
    void setPerspective(float fov, float aspectRatio, float near, float far);
    void setPosition(const glm::vec3& pos);
    void lookAt(const glm::vec3& target);
    void updateFromVehicle(const class Vehicle* vehicle, float deltaTime);
    
    const glm::mat4& getViewMatrix() const { return viewMatrix_; }
    const glm::mat4& getProjectionMatrix() const { return projectionMatrix_; }
    const glm::vec3& getPosition() const { return position_; }
    const glm::vec3& getDirection() const { return direction_; }

private:
    void updateViewMatrix();

    glm::vec3 position_;
    glm::vec3 target_;
    glm::vec3 direction_;
    glm::vec3 up_;
    
    glm::mat4 viewMatrix_;
    glm::mat4 projectionMatrix_;
    
    float fov_;
    float aspectRatio_;
    float nearPlane_;
    float farPlane_;
    
    // Chase camera
    float chaseCamDistance_;
    float chaseCamHeight_;
};

} // namespace OpenHorizon
