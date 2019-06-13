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
#include "Renderer.h"

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
            float m_Colors[108];

            VertexArray m_va;
            VertexBuffer m_vb;
            VertexBuffer m_vb_color;
            VertexBufferLayout m_layout;
            VertexBufferLayout m_layout_color;
            Shader m_shader;
            Renderer m_renderer;

            // MVP
            glm::vec3 m_camera_pos;
            glm::vec3 m_camera_tgt;

            glm::mat4 m_proj;
            glm::mat4 m_view;
    };
}
