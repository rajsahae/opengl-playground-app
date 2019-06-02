#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

GLFWwindow* InitWindow()
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return nullptr;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow( 600, 600, "OpenGL Pt2", nullptr, nullptr);
    if( window == nullptr ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // sync buffer swap with screen updates

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwTerminate();
        return nullptr;
    }

    fprintf(stderr, "GLEW Version: %s\n", glewGetString(GLEW_VERSION));
    fprintf(stderr, "GL Version: %s\n", glGetString(GL_VERSION));

    return window;
}

int main(void)
{
    GLFWwindow* window = InitWindow();
    if( window == nullptr ){
        fprintf( stderr, "Failed to initialize application window window.\n" );
        getchar();
        return 1;
    }

    const float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, // 0
         0.5f, -0.5f, 1.0f, 0.0f, // 1
         0.5f,  0.5f, 1.0f, 1.0f, // 2
        -0.5f,  0.5f, 0.0f, 1.0f // 3
    };

    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.AddFloat(2);
    layout.AddFloat(2);

    VertexArray va;
    va.AddBuffer(vb, layout);

    const unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    IndexBuffer ib(indices, 6);

    Shader shader("res/shaders/Texture.shader");

    float r = 0.3f;
    float increment = 0.05f;

    // Clear bindings
    va.Unbind();
    shader.Unbind();
    vb.Unbind();
    ib.Unbind();

    Renderer renderer;

    // Dark blue background
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));

    // Blending
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    //Texture texture("res/textures/natalie-face.jpg");
    Texture texture("res/textures/rocket.png");
    texture.Bind();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        // Uniforms are set per draw, attributes are per vertex
        shader.Bind();
        shader.SetUniform1i("u_Texture", 0);

        /* draw a triangle with modern opengl */
        renderer.Draw(va, ib, shader);

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

    glfwTerminate();
    return 0;
}
