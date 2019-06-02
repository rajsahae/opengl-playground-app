#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

class Shader
{
private:
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_Locations;

public:

    Shader(const std::string filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // Uniforms
    void SetUniform1f(std::string name, float v);
    void SetUniform4f(std::string name, float v1, float v2, float v3, float v4);
    void SetUniform1i(std::string name, int v);
    void SetUniformMat4f(std::string name, const glm::mat4 matrix);
    

private:

    struct ShaderSource {
        std::string VertexSource;
        std::string FragmentSource;
    };

    // Shader Compilation
    ShaderSource ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

    // Uniform retrieval
    int GetUniformLocation(const std::string name);
};


