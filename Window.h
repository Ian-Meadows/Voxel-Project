#ifndef WINDOW_H
#define WINDOW_H

#include "OpenGL_Includer.h"
#include "ErrorHandler.h"

#include "Scene.h"
#include "Input.h"
#include "Time.h"
#include "Camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <string>

#define NEAR_WORLD_PLANE 0.1f
#define FAR_WORLD_PLANE 1000.0f

namespace Window
{
    void Init(std::string name, bool vSync, int width, int height);

    void Start();


    int GetWidth();
    int GetHeight();
}


#endif