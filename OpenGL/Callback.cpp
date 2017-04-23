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
    if (key == GLFW_KEY_P) {
        if (x + 1 == 10)
            y = (y + 1) % 9;
        x = (x + 1) % 10;
    }
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (__glibc_unlikely(firstMouse)) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    camera.ProcessMouseMovement(xpos - lastX, lastY - ypos);

    lastX = xpos;
    lastY = ypos;
}
