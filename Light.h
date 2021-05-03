#ifndef LIGHT_H
#define LIGHT_H
#include "OpenGL_Includer.h"
#include "glm/glm.hpp"
#include "Shader.h"



#define SHADOW_WIDTH 1024
#define SHADOW_HEIGHT 1024

#define FAR_PLANE 25.0f
#define NEAR_PLANE 0.1f

class Scene;

class Light
{
public:
    Light(glm::vec3 position, bool realTime = false, float nearPlane = NEAR_PLANE, float farPlane = FAR_PLANE, bool hasAttenuation = true, float size = 0.2f);
    virtual ~Light();

    virtual void Update();

    virtual void BuildShadowMap(Shader* shader, Scene* scene, unsigned int shadowFBO, unsigned int shadowArrayMap, unsigned int number) final;

    bool IsRealtime() const { return realTimeShadows; }

    void Render(Shader* shader);

    glm::vec3 GetPosition() const { return position; }


    virtual void SetUpLight(Shader* shader, int location) final;

protected:
    glm::vec3 position;

private:
    unsigned int VAO, VBO;

    bool hasAttenuation = true;

    float nearPlane, farPlane;
    float size;

    int shadowWidth, shadowHeight;

    bool realTimeShadows = false;
};

#endif