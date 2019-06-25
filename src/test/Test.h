#pragma once

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include "glm/glm.hpp"

namespace test
{
    class Test
    {
        public:
            Test() {}
            virtual ~Test() {}

            virtual void OnUpdate(float deltaTime, glm::mat4 VP) {}
            virtual void OnRender() {}
            virtual void OnImGuiRender() {}
    };
}
