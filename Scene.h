#ifndef SCENE_H
#define SCENE_H
#include "OpenGL_Includer.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Camera.h"
#include "TextureAtlas.h"
#include "World.h"
#include "LightHandler.h"
#include "Input.h"

class Scene
{
public:
    Scene();
    ~Scene();
    void Render(glm::mat4 projection);

    void RenderScene(Shader* shader, glm::mat4 projection, glm::mat4 view);

    void RenderUI();

private:
    Shader* shader;

    unsigned int VAO;
    unsigned int VBO[2];

    TextureAtlas* textureAtlas = nullptr;


    World* world;


    void CheckForBlockChange();

    bool firstAmbient = true;

};


#endif