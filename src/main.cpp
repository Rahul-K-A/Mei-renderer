#include "mei-common.h"
#include "shaderProgram.h"

GLuint VAO, VBO, EBO;
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

uniform vec4 clr;
void main()
{
    fragColor = clr;
}
)gl";




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

void createSquare()
{
    float sPoints[] = {
        -0.5f, 0.5f, 0.f,
        -0.5f, -0.5f, 0.f,
         0.5f, 0.5f, 0.f,
         0.5f, -0.5f, 0.f
    };

    GLint indices[] = {
        0, 1, 2,
        2, 1 ,3
    };


    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sPoints), sPoints, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);
}

void createTriangle()
{
    // ALWAYS ENTER POINTS IN COUNTER CLOCKWISE ORDER
    float triPoints[] = {
    -0.5f, -0.5f, 0.0f,     //pos1
     1.f, 0.f, 0.0f,     //clr1
     0.5f,  -0.5f, 0.0f,  //pos2
     0.f,  1.f, 0.0f,  //clr2
     0.0f,  0.5f, 0.0f, //pos3
     0.0f,  0.f, 1.0f //clr3
    };  

    float colors[] = {
    };  
    //VBO - raw data sent to GPU, VAO - what is the data being sent and in what order 
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Bind VBO to Opengl State machine
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //Copy data to GPU, GL_STATIC_DRAW means we load data once and use it to draw many times
    glBufferData(GL_ARRAY_BUFFER, sizeof(triPoints), triPoints, GL_STATIC_DRAW);

    //Tell GPU what format the VBO data is in
    //Args attrib value (aka what is the layout value for the attribute that you set in shader, size of data in consideration (3 because we send a vector of 3 points), datatype, bNormalised, stride(aka how far away is the next data for the attribute), offset to first data of attribute in bytes)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)) );

    //Enable 0th attrib (positon) of VAO
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

}


void createTriangle1()
{
    // ALWAYS ENTER POINTS IN COUNTER CLOCKWISE ORDER
    float triPoints[] = {
    -1.f, -1.f, 0.0f,
     1.f,  -1.f, 0.0f,
     0.0f,  1.f, 0.0f
    };  
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
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    //Set callback for resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    ShaderProgram sProgram(vShader,fShader);
    createSquare();

    //Loop indefinitely
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        float tVal = glfwGetTime();
        float gV = sin(tVal)/2.f + 0.5f;
        float rV = cos(tVal)/2.f + 0.5f;
        float bV = tan(tVal)/2.f + 0.5f;
        int vertexClrLoc = sProgram.getUniformLocation("clr");
        sProgram.use();
        glUniform4f(vertexClrLoc, rV, gV, bV, 1.f);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);  
        glfwSwapBuffers(window);
        glfwPollEvents(); 
        process_input(window);


    }  
    return 0;
}
