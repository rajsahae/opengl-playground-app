#include "TestColoredCube.h"
#include "imgui.h"
#include "Debug.h"

namespace test
{
    TestColoredCube::TestColoredCube()
        : m_ClearColor { 0.3f, 0.5f, 0.8f, 1.0f },
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
        m_va(),
        m_vb(m_Positions, 3 * 36 * sizeof(float)),
        m_layout(),
        m_shader("res/shaders/OrthoUniform.shader"),
        m_camera_pos(glm::vec3(0, 0, 10)),
        m_camera_tgt(glm::vec3(0, 0, 0)),
        m_proj(glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f)),
        m_view(glm::lookAt(m_camera_pos, m_camera_tgt, glm::vec3(0, 1, 0)))
    {
        m_layout.AddFloat(3);
        m_va.AddBuffer(m_vb, m_layout);
    }

    TestColoredCube::~TestColoredCube()
    {
        m_shader.Unbind();
    }

    void TestColoredCube::OnRender()
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));

        m_view = glm::lookAt(m_camera_pos, m_camera_tgt, glm::vec3(0, 1, 0));

        m_va.Bind();
        m_shader.Bind();
        m_shader.SetUniformMat4f("u_MVP", m_proj * m_view);

        // 3 indices starting at 0 -> 1 triangle
        GLCall( glDrawArrays(GL_TRIANGLES, 0, 36) );
    }

    void TestColoredCube::OnImGuiRender()
    {
        ImGui::ColorEdit4("Clear Color", m_ClearColor);
        ImGui::SliderFloat3("Camera Pos", &m_camera_pos[0], -20, 20);
        ImGui::SliderFloat3("Camera Tgt", &m_camera_tgt[0], -20, 20);
    }
}
