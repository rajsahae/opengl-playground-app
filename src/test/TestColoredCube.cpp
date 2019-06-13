#include "TestColoredCube.h"
#include "imgui.h"
#include "Debug.h"

#include "glm/ext/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale
#include "glm/ext/matrix_clip_space.hpp" // glm::perspective
#include "glm/gtc/constants.hpp" // glm::pi

namespace test
{
    TestColoredCube::TestColoredCube()
        : m_ClearColor { 0.1f, 0.1f, 0.1f, 1.0f },
        m_Positions {
            -1.0f,-1.0f,-1.0f, // triangle 1 : begin
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // triangle 1 : end
            1.0f, 1.0f,-1.0f, // triangle 2 : begin
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f, // triangle 2 : end
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
        },
        m_Colors {
                    0.583f,  0.771f,  0.014f,
                    0.609f,  0.115f,  0.436f,
                    0.327f,  0.483f,  0.844f,
                    0.822f,  0.569f,  0.201f,
                    0.435f,  0.602f,  0.223f,
                    0.310f,  0.747f,  0.185f,
                    0.597f,  0.770f,  0.761f,
                    0.559f,  0.436f,  0.730f,
                    0.359f,  0.583f,  0.152f,
                    0.483f,  0.596f,  0.789f,
                    0.559f,  0.861f,  0.639f,
                    0.195f,  0.548f,  0.859f,
                    0.014f,  0.184f,  0.576f,
                    0.771f,  0.328f,  0.970f,
                    0.406f,  0.615f,  0.116f,
                    0.676f,  0.977f,  0.133f,
                    0.971f,  0.572f,  0.833f,
                    0.140f,  0.616f,  0.489f,
                    0.997f,  0.513f,  0.064f,
                    0.945f,  0.719f,  0.592f,
                    0.543f,  0.021f,  0.978f,
                    0.279f,  0.317f,  0.505f,
                    0.167f,  0.620f,  0.077f,
                    0.347f,  0.857f,  0.137f,
                    0.055f,  0.953f,  0.042f,
                    0.714f,  0.505f,  0.345f,
                    0.783f,  0.290f,  0.734f,
                    0.722f,  0.645f,  0.174f,
                    0.302f,  0.455f,  0.848f,
                    0.225f,  0.587f,  0.040f,
                    0.517f,  0.713f,  0.338f,
                    0.053f,  0.959f,  0.120f,
                    0.393f,  0.621f,  0.362f,
                    0.673f,  0.211f,  0.457f,
                    0.820f,  0.883f,  0.371f,
                    0.982f,  0.099f,  0.879f
        },
        m_va(),
        m_vb(m_Positions, 3 * 36 * sizeof(float)),
        m_vb_color(m_Colors, 3 * 36 * sizeof(float)),
        m_layout(),
        m_layout_color(),
        m_shader("res/shaders/Basic.shader"),
        m_renderer(),
        m_camera_pos(glm::vec3(4, 3, -3)),
        m_camera_tgt(glm::vec3(0, 0, 0)),
        m_proj(glm::perspective(glm::quarter_pi<float>(), 4.0f / 3.0f, 0.1f, 100.0f)),
        m_view(glm::lookAt(m_camera_pos, m_camera_tgt, glm::vec3(0, 1, 0)))
    {
        m_layout.AddFloat(3);
        m_layout_color.AddFloat(3);
        m_va.AddBuffer(m_vb, m_layout);
        m_va.AddBuffer(m_vb_color, m_layout_color, 1);
    }

    TestColoredCube::~TestColoredCube()
    {
        m_shader.Unbind();
    }

    void TestColoredCube::OnRender()
    {
        m_renderer.Clear(m_ClearColor);

        m_view = glm::lookAt(m_camera_pos, m_camera_tgt, glm::vec3(0, 1, 0));

        m_shader.Bind();
        m_shader.SetUniformMat4f("u_MVP", m_proj * m_view);

        // 3 indices starting at 0 -> 1 triangle
        m_renderer.Draw(m_va, m_shader, 36);
    }

    void TestColoredCube::OnImGuiRender()
    {
        ImGui::ColorEdit4("Clear Color", m_ClearColor);
        ImGui::SliderFloat3("Camera Pos", &m_camera_pos[0], -20, 20);
        ImGui::SliderFloat3("Camera Tgt", &m_camera_tgt[0], -20, 20);
    }
}
