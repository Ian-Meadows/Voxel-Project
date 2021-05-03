#include "Light.h"
#include "glm/gtc/matrix_transform.hpp"
#include "ErrorHandler.h"
#include "Scene.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Debugger.h"

Light::Light(glm::vec3 position, bool realTime, float nearPlane, float farPlane, bool hasAttenuation, float size)
{
    this->position = position;
    this->hasAttenuation = hasAttenuation;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;
    this->size = size;
    realTimeShadows = realTime;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    float pos[] =
    {
        0.0f, 0.0f, 0.0f
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3, &pos, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    ErrorHandler::ErrCheck("light init");

    ErrorHandler::ErrCheck("light cube map gen");
}
Light::~Light()
{

}

void Light::BuildShadowMap(Shader* shader, Scene* scene, unsigned int shadowFBO, unsigned int shadowArrayMap, unsigned int number)
{

    //create depth cubemap transformation matrices
    glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, nearPlane, farPlane);
    std::vector<glm::mat4> shadowViews;
    shadowViews.push_back(glm::lookAt(position, position + glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
    shadowViews.push_back(glm::lookAt(position, position + glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
    shadowViews.push_back(glm::lookAt(position, position + glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)));
    shadowViews.push_back(glm::lookAt(position, position + glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)));
    shadowViews.push_back(glm::lookAt(position, position + glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
    shadowViews.push_back(glm::lookAt(position, position + glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f)));


    //loop though each face on the cubemap and render the scene to it
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
    for(int i = 0; i < 6; ++i)
    {
        //must call this to bind the cubemap array with the framebuffer
        glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowArrayMap, 0, i + (number * 6));


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearDepth(1);
        
        //set light position in depth shader and render the scene
        shader->setVec3("lightPos", position);
        shader->setFloat("far_plane", farPlane);
        scene->RenderScene(shader, shadowProj, shadowViews[i]);
    }
    //revert back to the main framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    ErrorHandler::ErrCheck("World Shadow Map");
    
}

void Light::Update()
{

}

void Light::Render(Shader* shader)
{
    Update();
    glm::mat4 model(1.0);
    model = glm::translate(model, position);
    shader->setMat4("model", model);
    shader->setFloat("size", size);

    //draw the light as a square
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, 1);

    ErrorHandler::ErrCheck("light");
}

void Light::SetUpLight(Shader* shader, int location)
{
    //load lights into struct uniform array
    shader->setVec3("pointLights[" + std::to_string(location) + "].position", position);
    shader->setInt("pointLights[" + std::to_string(location) + "].hasAttenuation", hasAttenuation);
    shader->setFloat("pointLights[" + std::to_string(location) + "].farPlane", farPlane);
}