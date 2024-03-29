#include <stdio.h>
#include <chrono>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Test.h"
#include "TestMenu.h"
#include "TestClearColor.h"
#include "TestTriangle.h"
#include "TestUniform.h"
#include "TestMultipleObjects.h"
#include "TestBlending.h"
#include "TestColoredCube.h"
#include "TestBitmap.h"

#include "Debug.h"
#include "Controls.h"

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
    GLFWwindow* window = glfwCreateWindow( 800, 600, "OpenGL Pt2", nullptr, nullptr);
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
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // Enable depth test
    // Accept fragment if it closer to the camera than the former one
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glDepthFunc(GL_LESS));

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    const char* glsl_version = "#version 330";
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    test::Test *currentTest = nullptr;
    test::TestMenu *testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->RegisterTest<test::TestClearColor>("Clear Color");
    testMenu->RegisterTest<test::TestTriangle>("Triangle");
    testMenu->RegisterTest<test::TestUniform>("Uniform");
    testMenu->RegisterTest<test::TestMultipleObjects>("2D Textures");
    testMenu->RegisterTest<test::TestBlending>("Blending");
    testMenu->RegisterTest<test::TestColoredCube>("Colored Cube");
    testMenu->RegisterTest<test::TestBitmap>("Textured Cube");


    auto previous_time = std::chrono::steady_clock::now();

    /* Loop until the user closes the window */
    do {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        auto current_time = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed_ticks = current_time - previous_time;

        // build imgui window
        // Use a Begin/End pair to created a named window.
        if (currentTest)
        {
            float deltaTime = elapsed_ticks.count();
            controls::VP VP = controls::computeMatricesFromInputs(deltaTime);
            currentTest->OnUpdate(deltaTime, VP.ProjectionMatrix * VP.ViewMatrix);
            currentTest->OnRender();
            
            ImGui::Begin(testMenu->GetCurrentTestName().c_str());
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            if (currentTest != testMenu && ImGui::Button("<- Back"))
            {
                delete currentTest;
                currentTest = testMenu;
                testMenu->ResetTestName();
            }
            currentTest->OnImGuiRender();
            ImGui::End();
        }

        previous_time = current_time;

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
