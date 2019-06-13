#pragma once

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include "Test.h"
#include "Renderer.h"


namespace test
{
    class TestBitmap : public Test
    {
        public:
            TestBitmap();
            virtual ~TestBitmap() override;

            virtual void OnUpdate(float deltaTime) override;
            virtual void OnRender() override;
            virtual void OnImGuiRender() override;

        private:
            Renderer m_Renderer;
    };
}
