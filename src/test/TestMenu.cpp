#include "TestMenu.h"
#include "imgui.h"
#include <iostream>
#include "Debug.h"

namespace test
{
    TestMenu::TestMenu(Test*& currentTest) :
        m_CurrentTestName(m_TestMenuName),
        m_CurrentTest(currentTest)
    {
    }

    void TestMenu::OnRender()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void TestMenu::OnImGuiRender()
    {
        for (unsigned int i = 0; i < m_Tests.size(); i++)
        {
             if (i > 0 && i % 4 != 0)
                 ImGui::SameLine();
             else
                 ImGui::Separator();

             auto testPair = m_Tests.at(i);

             if (ImGui::Button(testPair.first.c_str()))
             {
                 m_CurrentTest = testPair.second();
                 m_CurrentTestName = testPair.first;
             }
        }
    }
}
