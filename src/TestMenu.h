#pragma once

#include "Test.h"

namespace test
{
    class TestMenu : public Test
    {
        private:
            std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
            Test*& m_CurrentTest;

        public:
            TestMenu(Test*& currentTest);

            void OnRender() override;
            void OnImGuiRender() override;

            template<typename T>
            void RegisterTest(const std::string& name)
            {
                std::cout << "Registering test: " << name << std::endl;
                m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
            }
    };
}
