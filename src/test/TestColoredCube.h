#pragma once

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include "Test.h"

#include <memory>
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test
{
    class TestColoredCube : public Test
    {
        public:
            TestColoredCube();
            ~TestColoredCube();

            void OnRender() override;
            void OnImGuiRender() override;

        private:
            float m_ClearColor[4];
            float m_Positions[108];

            VertexArray m_va;
            VertexBuffer m_vb;
            VertexBufferLayout m_layout;
            Shader m_shader;

            // MVP
            glm::vec3 m_camera_pos;
            glm::vec3 m_camera_tgt;

            glm::mat4 m_proj;
            glm::mat4 m_view;
    };
}