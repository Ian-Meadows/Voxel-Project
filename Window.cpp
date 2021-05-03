#include "Window.h"

//
// Print GLFW errors to stderr
//
static void error(int error,const char* text)
{
    fprintf(stderr,"GLFW error %d: %s\n",error,text);
}



namespace Window
{
    //private
    namespace
    {
        GLFWwindow* window;

        Scene* scene;
        

        double aspectRatio = 1;

        int width, height;

        glm::mat4 projection;
        float fov = 55;

        void Reshape(GLFWwindow* window,int width,int height)
        {
            //taken from ex06

            //  Get framebuffer dimensions (makes Apple work right)
            glfwGetFramebufferSize(window, &width, &height);
            //  Ratio of the width to the height of the window
            aspectRatio = (height>0) ? (double)width/height : 1;
            //  Set the viewport to the entire window
            glViewport(0,0, width,height);
            Window::width = width;
            Window::height = height;

            //  Set projection matrix
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            //  Perspective transformation
            gluPerspective(fov,aspectRatio,NEAR_WORLD_PLANE, FAR_WORLD_PLANE);
            //  Reset modelview
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            projection = glm::perspective(glm::radians(fov), (float)width / (float)height, NEAR_WORLD_PLANE, FAR_WORLD_PLANE);
        }

        //
        //  Initialize GLFW, GLEW and launch window
        //
        GLFWwindow* InitWindow(const char* title,int sync,int width,int height , void (*reshape)(GLFWwindow*,int,int) , void (*key)(GLFWwindow*,int,int,int,int))
        {
            //  Initialize GLFW
            if (!glfwInit()) ErrorHandler::Fatal("Cannot initialize glfw\n");

            //  Error callback
            glfwSetErrorCallback(error);

            //  Set window properties
            glfwWindowHint(GLFW_RESIZABLE,1);     //  Window can be resized
            glfwWindowHint(GLFW_DOUBLEBUFFER,1);  //  Window has double buffering
            glfwWindowHint(GLFW_DEPTH_BITS,24);   //  Prefer 24 depth bits
            glfwWindowHint(GLFW_ALPHA_BITS,8);    //  Prefer 8 alpha bits
            #ifdef APPLE_GL4
            //  Apple specific window properties to use with GLEW
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); 
            glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
            #endif

            //  Create window and make current
            GLFWwindow* window = glfwCreateWindow(width,height,title, NULL, NULL);
            if (!window) ErrorHandler::Fatal("Cannot create GLFW window\n");
            glfwMakeContextCurrent(window);

            //  Enable VSYNC (if selected)
            glfwSwapInterval(sync);

            #ifdef USEGLEW
            //  Initialize GLEW (if compiled in)
            if (glewInit()!=GLEW_OK) ErrorHandler::Fatal("Error initializing GLEW\n");
            #endif

            //  Set callback for window resize and make initial call
            if (reshape)
            {
                glfwSetWindowSizeCallback(window,reshape);
                //  Set initial window size and call reshape
                glfwGetWindowSize(window,&width,&height);
                reshape(window,width,height);
            }

            //  Set callback for keyboard input
            if (key) glfwSetKeyCallback(window,key);

            //  Return window
            return window;
        }


    }

    //public
    void Init(std::string name, bool vSync, int width, int height)
    {
        

        Window::width = width;
        Window::height = height;

        window = InitWindow(name.c_str(), vSync, width, height, &Reshape, NULL);
        glfwMakeContextCurrent(window);


        scene = new Scene();

        Camera::Init(window, glm::vec3(32.0, 104.0, 40.0));

        Time::Init(true);
        Input::InitInput(window);
    }

    void Start()
    {
        //TextureHandler::Preload();

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);

        

        
        ErrorHandler::ErrCheck("init");

        while(!glfwWindowShouldClose(window))
        {
            //update time to get fps and delta time
            Time::Update();

            //handle input
		    Input::ProcessInput();

            Camera::Update();

            //  Process any events
            scene->Render(projection);

            scene->RenderUI();

            Input::ClearOldInputs();

            ErrorHandler::ErrCheck("display");

            glFlush();
            glfwSwapBuffers(window);

            glfwPollEvents();
        }
        glfwDestroyWindow(window);
        glfwTerminate();

    }


    int GetWidth()
    {
        return width;
    }
    int GetHeight()
    {
        return height;
    }

    
}