#include "TestClearColor.h"

#include "Debug.h"
#include "imgui.h"

namespace test
{
    TestClearColor::TestClearColor()
        : Test("Test Clear Color"), m_ClearColor { 0.2f, 0.3f, 0.8f, 1.0f }
    {
    }

    TestClearColor::~TestClearColor()
    {
    }

    void TestClearColor::OnUpdate(float deltaTime)
    {
    }

    void TestClearColor::OnRender()
    {
        GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void TestClearColor::OnImGuiRender()
    {
        ImGui::SetNextWindowSize({ 300, 75 }, 0);
        ImGui::Begin(GetName().c_str());
        ImGui::ColorEdit4("Clear Color", m_ClearColor);
        ImGui::End();
    }
};
