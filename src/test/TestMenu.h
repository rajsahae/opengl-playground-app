#pragma once

#include "Test.h"

namespace test
{
    class TestMenu : public Test
    {
        private:
            std::string m_TestMenuName = "OpenGL Test Menu";
            std::string m_CurrentTestName;
            Test*& m_CurrentTest;
            std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;

        public:
            TestMenu(Test*& currentTest);

            void OnRender() override;
            void OnImGuiRender() override;

            std::string inline GetCurrentTestName() const { return m_CurrentTestName; }
            void inline ResetTestName() { m_CurrentTestName = m_TestMenuName; }

            template<typename T>
            void RegisterTest(const std::string& name)
            {
                std::cout << "Registering test: " << name << std::endl;
                m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
            }
    };
}
