#include "LightHandler.h"
#include <vector>
#include "Debugger.h"
#include "Scene.h"
#include "ErrorHandler.h"

namespace LightHandler
{
    namespace
    {
        //for rendering the "lights". They are just squares. Uses a geometry shader
        Shader* lightShader;

        //for generating the depthMap for multiple lights
        Shader* depthShader;

        
        std::vector<Light*> lights;

        //for multi light shadows
        unsigned int worldFBO, worldShadows;

        bool fullyBuilt = false;

        MovingLight* movingLight;

        void InitWorldShadows()
        {
            
            glGenTextures(1, &worldShadows);
            glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, worldShadows);
            //note: maxlights needs to be multiplied by 6 because there are 6 sides to a cube map
            glTexImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, MAX_LIGHTS * 6, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);   

            glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            glGenFramebuffers(1, &worldFBO);
            glBindFramebuffer(GL_FRAMEBUFFER, worldFBO);
            glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, worldShadows, 0);
            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE);



            //rebind back to normal
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            ErrorHandler::ErrCheck("World shadow init");
        }
    }
    void Init()
    {
        lightShader = new Shader("Shaders/Light.vert", "Shaders/Light.frag", "Shaders/Light.geom");
        depthShader = new Shader("Shaders/Voxel.vert", "Shaders/Depth.frag", "Shaders/Voxel.geom");

        movingLight = new MovingLight(glm::vec3(37, 104, 37));
        AddLight(movingLight);

        InitWorldShadows();
    }

    void RenderLights(glm::mat4 projection, glm::mat4 view)
    {
        lightShader->use();
        lightShader->setMat4("projection", projection);
        lightShader->setMat4("view", view);

        for(auto light : lights)
        {
            light->Render(lightShader);
        }
    }

    void BuildShadows(Scene* scene)
    {
        //move movinglight to camera position
        if(Input::GetKeyPressed(KeyCode::M))
        {
            movingLight->ChangeOffset(Camera::GetPosition());
        }
        //build multi light shadows
        depthShader->use();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //index for each lights within the cubemap array
        unsigned int i = 0;
        for(auto light : lights)
        {
            ErrorHandler::ErrCheck("light handler: lights");

            //only update lights that are either realtime lights of when a light needs to rebuild its shadow map
            if(light->IsRealtime() || !fullyBuilt)
            {
                light->BuildShadowMap(depthShader, scene, worldFBO, worldShadows, i);
            }
            //increase for each light. 
            ++i;
        }

        

        fullyBuilt = true;
    }

    void SetUpLights(Shader* shader)
    {
        shader->setInt("totalLights", lights.size());


        for(unsigned int i = 0; i < lights.size(); ++i)
        {
            lights[i]->SetUpLight(shader, i);
        }


        shader->setFloat("far_plane", FAR_PLANE);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, worldShadows);
    }

    void AddLight(Light* light)
    {
        //limit total lights
        if(lights.size() < MAX_LIGHTS)
        {
            lights.push_back(light);
        }
        
    }

    void RemoveLight(Light* light)
    {
        for(unsigned int i = 0; i < lights.size(); ++i)
        {
            if(lights[i] == light)
            {
                lights.erase(lights.begin() + i);
            }
        }
    }

    int GetTotalLightsInUse()
    {
        return lights.size();
    }

    void FullRebuildRequired()
    {
        fullyBuilt = false;
    }
}