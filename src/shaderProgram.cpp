#include "shaderProgram.h"
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram(std::string filePathVertex, std::string filePathFragment): shaderStatus(0), vShader(0), fShader(0), PID(0), isReady(GL_TRUE), infoLog(nullptr)
{
    std::ifstream fileHandler;
    std::string vshaderCode, fshaderCode;
    fileHandler.open(filePathVertex);
    if(fileHandler.is_open())
    {
        std::ostringstream ss1;
        ss1 << fileHandler.rdbuf();
        vshaderCode = ss1.str();
        ss1.clear();
        fileHandler.close();
    }
    else{
        std::cerr << "ERROR::COULD NOT READ VERTEX SHADER! CHECK PATH TO SHADER" << std::endl;
    }

    fileHandler.open(filePathFragment);
    if(fileHandler.is_open())
    {
        std::ostringstream ss2;
        ss2 << fileHandler.rdbuf();
        fshaderCode = ss2.str();
        ss2.clear();
        fileHandler.close();
    }
    else{
        std::cerr << "ERROR::COULD NOT READ FRAGMENT SHADER! CHECK PATH TO SHADER" << std::endl;
    }

    infoLog = new char[512];
    vShader = createShader(vshaderCode.c_str(), GL_VERTEX_SHADER);
    fShader = createShader(fshaderCode.c_str(), GL_FRAGMENT_SHADER);
    PID = createShaderProgram();


}


ShaderProgram::ShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode ): shaderStatus(0), vShader(0), fShader(0), PID(0), isReady(GL_TRUE), infoLog(nullptr)
{
    infoLog = new char[512];
    vShader = createShader(vertexShaderCode, GL_VERTEX_SHADER);
    fShader = createShader(fragmentShaderCode, GL_FRAGMENT_SHADER);
    PID = createShaderProgram();
}


GLint ShaderProgram::createShader(const char* code, const GLint shaderType)
{
    GLint shaderID;
    shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &code, NULL);
    glCompileShader(shaderID);
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderStatus);
    if(!shaderStatus)
    {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        isReady = GL_FALSE;
        return 0;
    }
    return shaderID;
}


GLint ShaderProgram::createShaderProgram()
{
    if(!isReady)
    {
        std::cerr<<"ERROR::SHADER::PROGRAM::ONE OF THE SHADERS HASNT BEEN COMPILED!" << std::endl;
        return 0;
    }
    GLint tPID = glCreateProgram();
    glAttachShader(tPID, vShader);
    glAttachShader(tPID, fShader);
    glLinkProgram(tPID);
    glGetProgramiv(tPID, GL_LINK_STATUS, &shaderStatus);
    if(!shaderStatus) {
        glGetProgramInfoLog(tPID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING FAILED\n" << infoLog << std::endl;
        isReady = GL_FALSE;
        return 0;     
    }
    return tPID;
}


void ShaderProgram::use()
{
    glUseProgram(PID);
}

GLint ShaderProgram::getUniformLocation(const char* uniformName){
    return glGetUniformLocation(PID, uniformName);
}

void ShaderProgram::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(PID, name.c_str()), (int)value); 
}
        
void ShaderProgram::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(PID, name.c_str()), value); 
}

void ShaderProgram::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(PID, name.c_str()), value); 
}

void ShaderProgram::stop()
{
    glUseProgram(0);
}


ShaderProgram::~ShaderProgram()
{
    if(infoLog)
    {
        delete infoLog;
    }
    glDeleteShader(vShader);
    glDeleteShader(fShader);
    glDeleteProgram(PID);
    PID = 0;
    fShader = 0;
    vShader = 0;
}