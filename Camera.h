#ifndef CAMERA_H
#define CAMERA_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Input.h"
#include "Time.h"

namespace Camera
{
    void Init(GLFWwindow* window, glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f));
    void Update();

    glm::vec3 GetPosition();
    glm::mat4 GetView();
    glm::vec3 GetFront();

    //returns a matrix without position
    glm::mat4 GetRotationView();

    void EnableCurser();
    void DisableCurser();
}



#endif