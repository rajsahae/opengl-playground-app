#include "TestBlending.h"

#include "Debug.h"
#include "imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test
{
    TestBlending::TestBlending() :
        m_ClearColor { 0.3f, 0.5f, 0.8f, 1.0f },
        m_ObjectColorA { 0.8f, 0.2f, 0.1f, 1.0f },
        m_ObjectColorB { 0.2f, 0.9f, 0.3f, 1.0f },
        m_EnableBlend(true),
        m_va(),
        m_layout(),
        m_shader("res/shaders/OrthoUniform.shader"),
        m_renderer(),
        m_proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
        m_view(glm::translate(glm::mat4(1.0f), glm::vec3(300, 0, 0))),
        m_translationA(200, 200, 0),
        m_translationB(300, 300, 0)
    {
        const float positions[] = {
            -100.0f, -100.0f, // 0
             100.0f, -100.0f, // 1
             100.0f,  100.0f, // 2
            -100.0f,  100.0f  // 3
        };

        const unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        m_ib = std::unique_ptr<IndexBuffer>(new IndexBuffer(&indices[0], 6));
        m_vb = std::unique_ptr<VertexBuffer>(new VertexBuffer(positions, 4 * 2 * sizeof(float)));

        m_layout.AddFloat(2);
        m_va.AddBuffer(*m_vb.get(), m_layout);
    }

    TestBlending::~TestBlending()
    {
        m_va.Unbind();
        m_shader.Unbind();
    }

    void TestBlending::OnUpdate(float deltaTime)
    {
    }

    void TestBlending::OnRender()
    {
        if (m_EnableBlend)
        {
            GLCall(glEnable(GL_BLEND));
            GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        }
        else
        {
            GLCall(glDisable(GL_BLEND));
        }

        m_renderer.Clear();
        GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
            glm::mat4 mvp = m_proj * m_view * model;
            m_shader.Bind();
            m_shader.SetUniformMat4f("u_MVP", mvp);
            m_shader.SetUniform4f("u_Color", m_ObjectColorA[0], m_ObjectColorA[1], m_ObjectColorA[2], m_ObjectColorA[3]);
            m_renderer.Draw(m_va, *m_ib.get(), m_shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationB);
            glm::mat4 mvp = m_proj * m_view * model;
            m_shader.Bind();
            m_shader.SetUniformMat4f("u_MVP", mvp);
            m_shader.SetUniform4f("u_Color", m_ObjectColorB[0], m_ObjectColorB[1], m_ObjectColorB[2], m_ObjectColorB[3]);
            m_renderer.Draw(m_va, *m_ib.get(), m_shader);
        }
    }

    void TestBlending::OnImGuiRender()
    {
        ImGui::ColorEdit4("Clear Color", m_ClearColor);
        ImGui::ColorEdit4("A Color", &m_ObjectColorA[0]);
        ImGui::ColorEdit4("B Color", &m_ObjectColorB[0]);
        ImGui::Checkbox("Enable Blend", &m_EnableBlend);
    }
};
