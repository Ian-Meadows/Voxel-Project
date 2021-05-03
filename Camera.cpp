#include "Camera.h"
#include "Debugger.h"


namespace Camera
{
    namespace
    {
        GLFWwindow* window;

        glm::mat4 view;
        glm::vec3 position;
        glm::vec3 rotation;

        


        glm::vec3 front;
        glm::vec3 up;

        bool showCurser = true;
        float sensitivity = 0.1f;
        float speed = 7.5f;
        glm::vec2 lastMousePos;
        bool hasLastMousePos = false;

        void UpdateView()
        {
            view = glm::lookAt(position, position + front, up);
        }

        void UpdateCurser()
        {
            if(showCurser)
            {
                hasLastMousePos = false;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            else
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
        }

        void CurserCheck()
        {
            if(Input::GetKeyPressed(KeyCode::L))
            {
                showCurser = !showCurser;
                UpdateCurser();
            }
        }

        void Movement()
        {
            float cameraSpeed = speed * Time::GetDeltaTime();
            if (Input::GetKeyHeld(KeyCode::W))
            {
                position += cameraSpeed * front;
            }
            if (Input::GetKeyHeld(KeyCode::S))
            {
                position -= cameraSpeed * front;
            }
            if (Input::GetKeyHeld(KeyCode::A))
            {
                position -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
            }  
            if (Input::GetKeyHeld(KeyCode::D))
            {
                position += glm::normalize(glm::cross(front, up)) * cameraSpeed;
            }
                
        }


        

        void Rotation()
        {
            glm::vec2 mousePos = Input::GetMousePosition();
            if(!hasLastMousePos)
            {
                lastMousePos = mousePos;
                hasLastMousePos = true;
            }

            glm::vec2 offset = mousePos - lastMousePos;
            lastMousePos = mousePos;

            offset *= sensitivity;

            //yaw
            rotation.x += offset.x;
            //pitch
            rotation.y -= offset.y;

            if (rotation.y > 89.0f)
            {
                rotation.y = 89.0f;
            }
            if (rotation.y < -89.0f)
            {
                rotation.y = -89.0f;
            }
                

            glm::vec3 newFront;
            newFront.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
            newFront.y = sin(glm::radians(rotation.y));
            newFront.z = sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
            front = glm::normalize(newFront);
        }

        void KeyRoation()
        {
            //have a consistent rotation across frame rates
            float rotSpeed = 70.0f * Time::GetDeltaTime();
            if(Input::GetKeyHeld(KeyCode::UP_ARROW))
            {
                rotation.y+=rotSpeed;
            }
            if(Input::GetKeyHeld(KeyCode::DOWN_ARROW))
            {
                rotation.y-=rotSpeed;
            }
            if(Input::GetKeyHeld(KeyCode::LEFT_ARROW))
            {
                rotation.x-=rotSpeed;
            }
            if(Input::GetKeyHeld(KeyCode::RIGHT_ARROW))
            {
                rotation.x+=rotSpeed;
            }

            if (rotation.y > 89.0f)
            {
                rotation.y = 89.0f;
            }
            if (rotation.y < -89.0f)
            {
                rotation.y = -89.0f;
            }
                

            glm::vec3 newFront;
            newFront.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
            newFront.y = sin(glm::radians(rotation.y));
            newFront.z = sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
            front = glm::normalize(newFront);
        }
    }
    void Init(GLFWwindow* window, glm::vec3 position, glm::vec3 rotation)
    {
        Camera::window = window;

        Camera::position = position;
        Camera::rotation = rotation;

        up = glm::vec3(0, 1.0, 0);
        front = glm::vec3(0, 0, 1.0);

        UpdateView();

        UpdateCurser();
    }

    void Update()
    {
        CurserCheck();
        Movement();

        if(!showCurser)
        {
            
            Rotation();

            
        }
        
        KeyRoation();


        UpdateView();

    }

    glm::mat4 GetRotationView()
    {
        return glm::lookAt(glm::vec3(0.0f), front, up);
    }

    glm::vec3 GetPosition()
    {
        return position;
    }
    glm::mat4 GetView()
    {
        return view;
    }

    void EnableCurser()
    {
        showCurser = true;
        UpdateCurser();
    }
    void DisableCurser()
    {
        showCurser = false;
        UpdateCurser();
    }
    glm::vec3 GetFront()
    {
        return front;
    }
}