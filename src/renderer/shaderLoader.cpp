
#include "renderer/shaderLoader.h"
#include <iostream>
#include <string>
#include <regex>

std::unordered_map<std::string, std::string> parseShaderSections(const std::string& fileContent);

ShaderLoader::ShaderLoader(FileSystem* fs) : fileSystem(fs) {}

ShaderLoader::~ShaderLoader() {
    for (auto& program : shaderPrograms) {
        glDeleteProgram(program.second);
    }
}

GLuint ShaderLoader::loadShader(const std::string& shaderPath) {
    std::string resolvedPath = fileSystem->resolvePath(shaderPath);
    if (!fileSystem->fileExists(resolvedPath)) {
        throw std::runtime_error("Shader file not found: " + resolvedPath);
    }

    std::string fileContent = fileSystem->readFile(resolvedPath);
    auto shaderSections = parseShaderSections(fileContent);

    if (shaderSections.find("vertex") == shaderSections.end()) {
        throw std::runtime_error("Vertex shader section not found in file: " + resolvedPath);
    }
    if (shaderSections.find("fragment") == shaderSections.end()) {
        throw std::runtime_error("Fragment shader section not found in file: " + resolvedPath);
    }

    GLuint vertexShader = compileShader(shaderSections["vertex"], GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(shaderSections["fragment"], GL_FRAGMENT_SHADER);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    checkCompileErrors(program, GL_LINK_STATUS);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    shaderPrograms[shaderPath] = program;

    return program;
}


std::string ShaderLoader::readFile(const std::string& filePath) const {
    std::string resolvedPath = fileSystem->resolvePath(filePath);
    if (!fileSystem->fileExists(resolvedPath)) {
        throw std::runtime_error("Shader file does not exist: " + resolvedPath);
    }
    return fileSystem->readFile(resolvedPath);
}

void ShaderLoader::useShader(GLuint programID) const {
    glUseProgram(programID);
}

void ShaderLoader::deleteShader(GLuint programID) {
    glDeleteProgram(programID);
}


void ShaderLoader::checkCompileErrors(GLuint shader, GLenum type) const {
    GLint success;
    GLchar infoLog[1024];

    if (type != GL_LINK_STATUS) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }
}

GLuint ShaderLoader::compileShader(const std::string& source, GLenum shaderType) const {
    std::cout << "Compiling shader of type: " << shaderType << std::endl;
    GLuint shader = glCreateShader(shaderType);
    const char* sourceCStr = source.c_str();
    std::cout << "setting source..." << sourceCStr << std::endl;
    glShaderSource(shader, 1, &sourceCStr, nullptr);
    std::cout << "Compiling shader..." << std::endl;
    glCompileShader(shader);
    std::cout << "Checking for shader compilation errors..." << std::endl;
    checkCompileErrors(shader, shaderType);
    return shader;
}

std::unordered_map<std::string, std::string> parseShaderSections(const std::string& fileContent) {
    std::unordered_map<std::string, std::string> shaderSections;
    const std::regex typeRegex(R"(^#type\s+(\w+))");
    std::smatch match;

    std::string currentType;
    std::stringstream currentCode;

    std::istringstream stream(fileContent);
    std::string line;
    while (std::getline(stream, line)) {
        if (std::regex_match(line, match, typeRegex)) {
            if (!currentType.empty()) {
                shaderSections[currentType] = currentCode.str();
            }
            currentType = match[1].str();
            currentCode.str("");
            currentCode.clear();
        } else if (!currentType.empty()) {
            currentCode << line << '\n';
        }
    }

    if (!currentType.empty()) {
        shaderSections[currentType] = currentCode.str();
    }

    return shaderSections;
}
