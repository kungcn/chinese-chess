//
// Created by hao on 4/22/17.
//

#include "Camera.h"

Camera* CameraHandler::camera = new Camera(vec3(0, 10, 3));

mat4 Camera::GetViewMatrix() {
    return lookAt(Position , Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime) {
    GLfloat velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD) {
        Position += Front * velocity;
    }
    if (direction == BACKWARD) {
        Position -= Front * velocity;
    }
    if (direction == LEFT) {
        Position -= Right * velocity;
    }
    if (direction == RIGHT) {
        Position += Right * velocity;
    }
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch) {
        Pitch = std::min(Pitch, (GLfloat) 89);
        Pitch = std::max(Pitch, (GLfloat) -89);
    }

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yoffset) {
    if (Zoom >= 1 && Zoom <= 45) {
        Zoom -= yoffset;
    }
    Zoom = std::min(Zoom, (GLfloat) 45);
    Zoom = std::max(Zoom, (GLfloat) 1);
}

void Camera::updateCameraVectors() {
    vec3 front;
    front.x = cos(radians(Yaw)) * cos(radians(Pitch));
    front.y = sin(radians(Pitch));
    front.z = sin(radians(Yaw)) * cos(radians(Pitch));

    Front = normalize(front);

    Right = normalize(cross(Front, WorldUp));
    Up = normalize((cross(Right, Front)));
}