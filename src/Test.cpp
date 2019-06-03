#include "Test.h"
#include "imgui.h"
#include <iostream>
#include "Debug.h"

namespace test
{
    TestMenu::TestMenu(Test*& currentTest) : m_CurrentTest(currentTest) {}

    void TestMenu::OnRender()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void TestMenu::OnImGuiRender()
    {
       for (auto testPair : m_Tests)
       {
            if (ImGui::Button(testPair.first.c_str()))
                m_CurrentTest = testPair.second();
       }
    }
}
