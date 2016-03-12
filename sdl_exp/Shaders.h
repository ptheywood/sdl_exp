#ifndef __Shaders_h__
#define __Shaders_h__

//Define EXIT_ON_ERROR to cause the program to exit when shader compilation fails

#include "GLcheck.h"

#include <regex>

class Shaders
{
public:
    Shaders(char* vertexShaderPath=0, char* fragmentShaderPath=0, char* geometryShaderPath=0);
    ~Shaders();

    bool hasVertexShader() const;
    bool hasFragmentShader() const;
    bool hasGeometryShader() const;
    bool getCompileSuccess() const;

    void createShaders();
    bool reloadShaders(bool silent = false);
    void useProgram();
    void clearProgram();
    void setUniformi(int location, int value);
    void setUniformMatrix4fv(int location, GLfloat* value);

private:
    char* vertexShaderPath;
    char* fragmentShaderPath;
    char* geometryShaderPath;

    int vertexShaderId;
    int fragmentShaderId;
    int geometryShaderId;
    unsigned int vertexShaderVersion;
    unsigned int fragmentShaderVersion;
    unsigned int geometryShaderVersion;
    int programId;
    bool compileSuccessFlag;

    char* loadShaderSource(char* file);
    void destroyShaders();
    void destroyProgram();
    bool checkShaderCompileError(int shaderId, char* shaderPath);
    bool checkProgramCompileError(int programId);

    std::regex versionRegex;
    unsigned int findShaderVersion(const char *shaderSource);
    int Shaders::findUniformLocation(const char *shaderSource, const char *uniformName);

};

#endif //ifndef __Shaders_h__