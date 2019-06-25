#pragma once

#include <memory>

#include "Test.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test
{
    class TestBlending : public Test
    {
        public:
            TestBlending();
            ~TestBlending();

            void OnRender() override;
            void OnImGuiRender() override;

        private:
            float m_ClearColor[4];
            float m_ObjectColorA[4];
            float m_ObjectColorB[4];
            bool m_EnableBlend;

            // opengl members
            VertexArray m_va;
            VertexBufferLayout m_layout;
            Shader m_shader;
            Renderer m_renderer;

            std::unique_ptr<IndexBuffer> m_ib;
            std::unique_ptr<VertexBuffer> m_vb;

            // MVP members
            glm::mat4 m_proj;
            glm::mat4 m_view;

            // Translation members
            glm::vec3 m_translationA;
            glm::vec3 m_translationB;
    };
    
}
