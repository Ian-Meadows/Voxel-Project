#ifndef LIGHT_HANDLER_H
#define LIGHT_HANDLER_H
#define MAX_LIGHTS 25
#include "Light.h"
#include "MovingLight.h"
#include "Shader.h"

class Scene;

namespace LightHandler
{
    void Init();

    //TODO: remove RenderLights tmp function
    void RenderLights(glm::mat4 projection, glm::mat4 view);

    void BuildShadows(Scene* scene);

    void SetUpLights(Shader* shader);

    void AddLight(Light* light);
    void RemoveLight(Light* light);

    int GetTotalLightsInUse();

    //when every light needs to rebuild their shadow map
    void FullRebuildRequired();
}

#endif