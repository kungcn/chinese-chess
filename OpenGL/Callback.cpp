//
// Created by hao on 4/22/17.
//

#include "Callback.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
    if (key == GLFW_KEY_I && action == GLFW_PRESS) {
        LightHandler::light->Triggle(SPOT_LIGHT);
    }
    if (key == GLFW_KEY_O && action == GLFW_PRESS) {
        LightHandler::light->Triggle(DIRECTIONAL_LIGHT);
    }
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        LightHandler::light->Triggle(POINT_LIGHT);
    }
    if (key == GLFW_KEY_U && action == GLFW_PRESS) {
        skyboxEnable = !skyboxEnable;
    }
    if (key == GLFW_KEY_M && action == GLFW_PRESS) {
        modelEnable = !modelEnable;
    }
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (__glibc_unlikely(firstMouse)) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    CameraHandler::camera->ProcessMouseMovement(xpos - lastX, lastY - ypos);

    lastX = xpos;
    lastY = ypos;
}
