#include "mei-common.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0, width, height);
}

int main()
{
    glfwInit();
    //Use OpenGL 3.3 with core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create Window 800x600
    GLFWwindow* window = glfwCreateWindow(800,600,"My Window",NULL,NULL);
    if(window == NULL)
    {
        std::cout<<"Failed to create window!\n";
        glfwTerminate();
        return -1;
    }
    //Make the window the current context for draws
    glfwMakeContextCurrent(window);

    //Load GLAD 
    if(!gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ))
    {
        std::cout<<"Failed to load glad!\n";
        return -1;
    }

    //Define the position of your view port in window coordinates and the size
    glViewport(0,0,800,600);

    //Set callback for resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Loop indefinitely
    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }  
    return 0;
}
