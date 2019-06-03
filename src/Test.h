#pragma once

#include <string>
#include <vector>
#include <functional>
#include <iostream>

namespace test
{
    class Test
    {
        public:
            Test() {}
            virtual ~Test() {}

            virtual void OnUpdate(float deltaTime) {}
            virtual void OnRender() {}
            virtual void OnImGuiRender() {}
    };
}
