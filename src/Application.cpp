#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

struct ShaderSource {
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderSource ParseShader(const std::string& filepath)
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

static unsigned int CompileShader(unsigned int type, const std::string& source)
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

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
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

int main(void)
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return 1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow( 600, 600, "OpenGL Pt2", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return 2;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // sync buffer swap with screen updates

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return 3;
    }

    printf("GLEW Version: %s\n", glewGetString(GLEW_VERSION));
    printf("GL Version: %s\n", glGetString(GL_VERSION));

    const float positions[] = {
        -0.5f, -0.5f, // 0
         0.5f, -0.5f, // 1
         0.5f,  0.5f, // 2
        -0.5f,  0.5f, // 3
    };

    const unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Dark blue background
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));

    VertexArray va;
    VertexBuffer vb(positions, 4 * 2 * sizeof(float));
    VertexBufferLayout layout;
    layout.AddFloat(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    ShaderSource shaderSource = ParseShader("res/shaders/Basic.shader");
    std::cout << "Vertex shader:" << std::endl << shaderSource.VertexSource << std::endl;
    std::cout << "Fragment shader:" << std::endl << shaderSource.FragmentSource << std::endl;

    unsigned int shader = CreateShader(shaderSource.VertexSource, shaderSource.FragmentSource);
    GLCall(glUseProgram(shader));

    // Uniforms are set per draw, attributes are per vertex
    GLCall(int colorLocation = glGetUniformLocation(shader, "u_Color"));
    assert(colorLocation != GL_INVALID_VALUE);
    assert(colorLocation != GL_INVALID_OPERATION);
    assert(colorLocation != -1);

    float r = 0.3f;
    float increment = 0.05f;

    // Clear bindings
    GLCall(glUseProgram(0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        // Rebind
        GLCall(glUseProgram(shader));
        GLCall(glUniform4f(colorLocation, r, 0.3f, 0.8f, 1.0f));

        va.Bind();
        ib.Bind();

        /* draw a triangle with modern opengl */
        GLCall( glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, NULL) );

        if (r > 1.0f)
            increment = -0.05f;
        if (r < 0.0f)
            increment = 0.05f;

        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    GLCall(glDeleteProgram(shader));
    glfwTerminate();
    return 0;
}
