#pragma once

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include "Test.h"
#include "Renderer.h"
#include "BMPImageReader.h"


namespace test
{
    class TestBitmap : public Test
    {
        public:
            TestBitmap();
            virtual ~TestBitmap() override;

            void OnUpdate(float deltaTime, glm::mat4 VP) override;
            void OnRender() override;
            void OnImGuiRender() override;

        private:
            Renderer m_Renderer;
            BMPImageReader m_BIR;
            unsigned int m_TextureID;

            float m_ClearColor[4];
            float m_Positions[108];
            float m_TexCoords[108];
            float m_RotationalVelocity; // radians per sec

            VertexArray m_va;
            VertexBuffer m_vb;
            VertexBuffer m_vb_texture;
            VertexBufferLayout m_layout;
            VertexBufferLayout m_layout_texture;
            Shader m_shader;
            Renderer m_renderer;

            // MVP
            glm::vec3 m_camera_pos;
            glm::vec3 m_camera_tgt;

            glm::mat4 m_model;
            glm::mat4 m_MVP;
    };
}
