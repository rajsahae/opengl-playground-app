#include "Renderer.h"
#include "Shader.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string filepath)
    : m_Locations()
{
    ShaderSource shaderSource = ParseShader(filepath);

#ifdef DEBUG
    std::cout << "Vertex shader:" << std::endl << shaderSource.VertexSource << std::endl;
    std::cout << "Fragment shader:" << std::endl << shaderSource.FragmentSource << std::endl;
#endif

    m_RendererID = CreateShader(shaderSource.VertexSource, shaderSource.FragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

Shader::ShaderSource Shader::ParseShader(const std::string& filepath)
{
    enum class ShaderType { None = -1, Vertex = 0, Fragment = 1 };

    std::ifstream stream(filepath);
    std::stringstream ss[2];
    std::string line;
    ShaderType currentType = ShaderType::None;

    while(getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                currentType = ShaderType::Vertex;
            else if (line.find("fragment") != std::string::npos)
                currentType = ShaderType::Fragment;
        }
        else
        {
            // append to appropriate string stream
            ss[(int)currentType] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, NULL));
    GLCall(glCompileShader(id));

    int compileStatus;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus));
    if (compileStatus == GL_FALSE)
    {
        int log_length = 0;
        char message[1024];
        GLCall(glGetShaderInfoLog(id, 1024, &log_length, message));

        std::string shaderType = (type == GL_VERTEX_SHADER ? "vertex" : "fragment");
        std::cout << shaderType << " shader compile failed:" << std::endl;
        std::cout << message << std::endl;

        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());
    GLCall(unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader));
    GLCall(unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader));

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    int program_linked;
    GLCall(glGetProgramiv(program, GL_LINK_STATUS, &program_linked));
    if (program_linked == GL_FALSE)
    {
        int log_length = 0;
        char message[1024];
        GLCall(glGetProgramInfoLog(program, 1024, &log_length, message));
        std::cout << "Program validation failed:" << std::endl;
        std::cout << message << std::endl;
        return 0;
    }

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

void Shader::SetUniform1i(std::string name, int v)
{
    GLCall(glUniform1i(GetUniformLocation(name), v));
}

void Shader::SetUniform1f(std::string name, float v)
{
    GLCall(glUniform1f(GetUniformLocation(name), v));
}

void Shader::SetUniform4f(std::string name, float v1, float v2, float v3, float v4)
{
    GLCall(glUniform4f(GetUniformLocation(name), v1, v2, v3, v4));
}

int Shader::GetUniformLocation(const std::string name)
{
    auto search = m_Locations.find(name);
    if (search != m_Locations.end())
        return m_Locations[name];

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));

    assert(location != GL_INVALID_VALUE);
    assert(location != GL_INVALID_OPERATION);

    if (location == -1)
        std::cout << "Uniform location not found: " << name << std::endl;

    m_Locations[name] = location;

    return location;
}
