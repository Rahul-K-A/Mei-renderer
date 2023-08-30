#include "mei-common.h"

GLuint vertexShader, fragShader, VAO, VBO, shaderProgram;
const char* vShader = R"gl(
#version 400 
layout (location = 0) in vec3 point;
void main()
{
    gl_Position = vec4(point, 1.0);
}
)gl";

const char* fShader = R"gl(
#version 400 
out vec4 fragColor;
void main()
{
    fragColor = vec4(1.f, 0, 1.f, 1.0);
}
)gl";



float triPoints[] = {
    -1.f, -1.f, 0.0f,
     1.f,  -1.f, 0.0f,
     0.0f,  1.f, 0.0f
};  

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0, width, height);
}

//Callback function for closing window when pressing ESC
void process_input(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }
}

void createTriangle()
{
    //VBO - raw data sent to GPU, VAO - what is the data being sent and in what order 
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Bind VBO to Opengl State machine
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //Copy data to GPU, GL_STATIC_DRAW means we load data once and use it to draw many times
    glBufferData(GL_ARRAY_BUFFER, sizeof(triPoints), triPoints, GL_STATIC_DRAW);

    //Tell GPU what format the VBO data is in
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //Enable 0th attrib (positon) of VAO
    glEnableVertexAttribArray(0);
}

void createShaders()
{
    GLint success;
    char infoLog[512];
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    // index of shader, number of strings being passed, address to string array, address to length array (only needed if passing multiple strings)
    glShaderSource(vertexShader, 1, &vShader, NULL );

    //Compile shader
    glCompileShader(vertexShader);

    //Get status of shader
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glShaderSource(fragShader, 1, &fShader, NULL );
    //Compile shader
    glCompileShader(fragShader);

    //Get status of shader
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING FAILED\n" << infoLog << std::endl;     
    }

    std::cout<<"Created shaders\n";
}


int main()
{
    glfwInit();
    //Use OpenGL 3.3 with core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create Window 800x600
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"My Window",NULL,NULL);
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
    glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);

    //Set callback for resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    createShaders();

    createTriangle();
    //Loop indefinitely
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);  
        glfwSwapBuffers(window);
        glfwPollEvents(); 
        process_input(window);


    }  
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);  
    return 0;
}
