#pragma once

#include <glad/glad.h>
#include <iostream>
#include <string>
#include "utility/FS.h"

class ShaderLoader {
public:
    ShaderLoader(FileSystem* fs);
    ~ShaderLoader();

    GLuint loadShader(const std::string& shaderPath);
    void useShader(GLuint programID) const;
    void deleteShader(GLuint programID);

private:
    std::string readFile(const std::string& filePath) const;
    GLuint compileShader(const std::string& source, GLenum shaderType) const;
    void checkCompileErrors(GLuint shader, GLenum type) const;

    std::unordered_map<std::string, GLuint> shaderPrograms;
    FileSystem* fileSystem; // Pointer to the FileSystem instance
};
