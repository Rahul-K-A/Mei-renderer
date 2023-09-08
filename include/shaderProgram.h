#ifndef SHADER_H
#define SHADER_H
#include "mei-common.h"

class ShaderProgram
{
    public:
        ShaderProgram(const char * ShaderCodeVertex, const char* ShaderCodeFragment);
        ShaderProgram(std::string filePathVertex, std::string filePathFragment);
        GLint getUniformLocation(const char* uniformName);
        ~ShaderProgram();
        void useShaderProgram();

    private:
        GLint createShader(const char* code, const int shaderType);
        GLint createShaderProgram();
        GLint shaderStatus;
        GLuint vShader, fShader, PID;
        GLboolean isReady;
        char* infoLog;



};


#endif //SHADER_H