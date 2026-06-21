#include "engine/rendering/Camera.h"
#include "../physics/Vehicle.h"
#include <glm/gtc/matrix_transform.hpp>

namespace OpenHorizon {

Camera::Camera()
    : position_(0.0f, 4.0f, -10.0f),
      target_(0.0f, 0.0f, 0.0f),
      direction_(0.0f, 0.0f, 1.0f),
      up_(0.0f, 1.0f, 0.0f),
      fov_(65.0f),
      aspectRatio_(16.0f / 9.0f),
      nearPlane_(0.1f),
      farPlane_(1000.0f),
      chaseCamDistance_(9.0f),
      chaseCamHeight_(4.0f) {
    updateViewMatrix();
    setPerspective(fov_, aspectRatio_, nearPlane_, farPlane_);
}

void Camera::setPerspective(float fov, float aspectRatio, float near, float far) {
    fov_ = fov;
    aspectRatio_ = aspectRatio;
    nearPlane_ = near;
    farPlane_ = far;
    projectionMatrix_ = glm::perspective(
        glm::radians(fov),
        aspectRatio,
        near,
        far
    );
}

void Camera::setPosition(const glm::vec3& pos) {
    position_ = pos;
    updateViewMatrix();
}

void Camera::lookAt(const glm::vec3& target) {
    target_ = target;
    direction_ = glm::normalize(target_ - position_);
    updateViewMatrix();
}

void Camera::updateFromVehicle(const Vehicle* vehicle, float deltaTime) {
    if (!vehicle) return;
    
    // Chase camera following vehicle
    glm::vec3 vehiclePos = vehicle->getPosition();
    float heading = vehicle->getHeading();
    
    glm::vec3 desiredPos = vehiclePos;
    desiredPos.x -= std::sin(heading) * chaseCamDistance_;
    desiredPos.y += chaseCamHeight_;
    desiredPos.z -= std::cos(heading) * chaseCamDistance_;
    
    // Smooth camera movement
    position_ = glm::mix(position_, desiredPos, deltaTime * 3.0f);
    
    glm::vec3 lookTarget = vehiclePos;
    lookTarget.y += 1.5f;
    target_ = glm::mix(target_, lookTarget, deltaTime * 2.0f);
    
    updateViewMatrix();
}

void Camera::updateViewMatrix() {
    viewMatrix_ = glm::lookAt(position_, target_, up_);
}

} // namespace OpenHorizon
