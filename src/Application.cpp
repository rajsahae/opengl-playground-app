#include <stdio.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "TestClearColor.h"
#include "TestTriangle.h"
#include "TestUniform.h"
#include "TestMultipleObjects.h"

#include "Debug.h"

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
    GLFWwindow* window = glfwCreateWindow( 960, 540, "OpenGL Pt2", nullptr, nullptr);
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

    // Blending
    // TODO: After getting the test framework going, might be nice to add a test to play with blending.
    // Have some color squares that we can move around on top of each other and some selections
    // to pick the different types of blending?
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    const char* glsl_version = "#version 330";
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    int currentSelection = -1;
    int radioSelection = 0;
    test::Test *test;

    /* Loop until the user closes the window */
    do {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // build imgui window
        // Use a Begin/End pair to created a named window.
        {
            ImGui::Begin("OpenGL Test Window");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::RadioButton("ClearColor",      &radioSelection, 0); ImGui::SameLine();
            ImGui::RadioButton("Triangle",        &radioSelection, 1); ImGui::SameLine();
            ImGui::RadioButton("Uniform",         &radioSelection, 2); ImGui::SameLine();
            ImGui::RadioButton("MultipleObjects", &radioSelection, 3);
            ImGui::End();
        }

        if (currentSelection != radioSelection)
        {
            switch(radioSelection)
            {
                case 0 : delete test;
                         test = new test::TestClearColor();
                         break;
                case 1 : delete test;
                         test = new test::TestTriangle();
                         break;
                case 2 : delete test;
                         test = new test::TestUniform();
                         break;
                case 3 : delete test;
                         test = new test::TestMultipleObjects();
                         break;
            }
            currentSelection = radioSelection;
        }

        test->OnUpdate(0.0f);
        test->OnRender();
        test->OnImGuiRender();

        // imgui draw
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
}
