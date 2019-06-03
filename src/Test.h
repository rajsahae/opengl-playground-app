#pragma once

#include <string>

namespace test
{
    class Test
    {
        private:
            std::string m_Name;

        public:
            Test() {}
            Test(const std::string& name) { m_Name = name; }
            virtual ~Test() {}

            virtual void OnUpdate(float deltaTime) {}
            virtual void OnRender() {}
            virtual void OnImGuiRender() {}

            std::string inline GetName() { return m_Name; }
    };
}
