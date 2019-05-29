#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    int compileStatus;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == GL_FALSE)
    {
        int log_length = 0;
        char message[1024];
        glGetShaderInfoLog(id, 1024, &log_length, message);

        std::string shaderType = (type == GL_VERTEX_SHADER ? "vertex" : "fragment");
        std::cout << shaderType << " shader compile failed:" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    int program_linked;
    glGetProgramiv(program, GL_LINK_STATUS, &program_linked);
    if (program_linked == GL_FALSE)
    {
        int log_length = 0;
        char message[1024];
        glGetProgramInfoLog(program, 1024, &log_length, message);
        std::cout << "Program validation failed:" << std::endl;
        std::cout << message << std::endl;
        return 0;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

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
    GLFWwindow* window = glfwCreateWindow( 600, 400, "OpenGL Pt2", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return 2;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return 3;
    }

    printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Status: Using GL %s\n", glGetString(GL_VERSION));

    float positions[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    // Dark blue background
    // glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // UGH I forgot all about this. On MacOS you have to create the VAO or it doesn't work
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int buffer;
    glGenBuffers(1, &buffer);

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), positions, GL_STATIC_DRAW);

    // define vertex layout
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    ShaderSource shaderSource = ParseShader("res/shaders/Basic.shader");
    std::cout << "Vertex shader:" << std::endl << shaderSource.VertexSource << std::endl;
    std::cout << "Fragment shader:" << std::endl << shaderSource.FragmentSource << std::endl;

    unsigned int shader = CreateShader(shaderSource.VertexSource, shaderSource.FragmentSource);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* draw a triangle with modern opengl */
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
