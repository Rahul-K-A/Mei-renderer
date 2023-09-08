#ifndef SHADER_H
#define SHADER_H
#include "mei-common.h"

/* Class that handles all shader and shader program code*/
class ShaderProgram
{
    public:
        /* Initialise shader program with code of vertex and fragment shaders*/
        ShaderProgram(const char * ShaderCodeVertex, const char* ShaderCodeFragment);
        /* Initialise shader program with path to vertex and fragment shaders*/
        ShaderProgram(std::string filePathVertex, std::string filePathFragment);
        /* Use the program within the render loop*/
        void use();

        /* Utility function to get the location of any uniform variable from either of the shaders.
            Use for things like vecs and matrices.
        */
        GLint getUniformLocation(const char* uniformName);
        /* Reset the shader program and use nothing*/
        static void stop();

        /*Utility function to set a Boolean value uniform variable*/
        void setBool(const std::string &name, bool value) const;

        /*Utility function to set a Integer value uniform variable*/
        void setInt(const std::string &name, int value) const;
        
        /*Utility function to set a floating point value uniform variable*/
        void setFloat(const std::string &name, float value) const;

        ~ShaderProgram();

    private:
        GLint createShader(const char* code, const int shaderType);
        GLint createShaderProgram();
        GLint shaderStatus;
        GLuint vShader, fShader, PID;
        GLboolean isReady;
        char* infoLog;



};


#endif //SHADER_H