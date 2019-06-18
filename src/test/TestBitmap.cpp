
#include "TestBitmap.h"
#include "imgui.h"
#include "Debug.h"

#include "glm/ext/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale
#include "glm/ext/matrix_clip_space.hpp" // glm::perspective
#include "glm/gtc/constants.hpp" // glm::pi

namespace test
{
    TestBitmap::TestBitmap() :
        m_Renderer(),
        m_BIR(),
        m_ClearColor{1.0f, 1.0f, 1.0f, 1.0f},
        m_Positions {
            -1.0f,-1.0f,-1.0f, // 0.0f, 0.0f, // triangle 1 : begin
            -1.0f,-1.0f, 1.0f, // 1.0f, 0.0f, 
            -1.0f, 1.0f, 1.0f, // 1.0f, 1.0f, // triangle 1 : end
            1.0f, 1.0f,-1.0f,  // 0.0f, 1.0f, // triangle 2 : begin
            -1.0f,-1.0f,-1.0f, // 0.0f, 1.0f, 
            -1.0f, 1.0f,-1.0f, // 1.0f, 1.0f, // triangle 2 : end
            1.0f,-1.0f, 1.0f,  // 1.0f, 1.0f, // triangle 3 : begin
            -1.0f,-1.0f,-1.0f, // 0.0f, 0.0f,
            1.0f,-1.0f,-1.0f,  // 1.0f, 0.0f, // triangle 3 : end
            1.0f, 1.0f,-1.0f,  // 0.0f, 1.0f, // triangle 4 : begin
            1.0f,-1.0f,-1.0f,  // 0.0f, 0.0f,
            -1.0f,-1.0f,-1.0f, // 1.0f, 0.0f, // triangle 4 : end
            -1.0f,-1.0f,-1.0f, // 0.0f, 0.0f, // triangle 5 : begin
            -1.0f, 1.0f, 1.0f, // 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f, // 0.0f, 1.0f, // triangle 5 : end
            1.0f,-1.0f, 1.0f,  // 1.0f, 1.0f, // triangle 6 : begin
            -1.0f,-1.0f, 1.0f, // 0.0f, 1.0f,
            -1.0f,-1.0f,-1.0f, // 0.0f, 0.0f, // triangle 6 : end
            -1.0f, 1.0f, 1.0f, // 0.0f, 1.0f, // triangle 7 : begin
            -1.0f,-1.0f, 1.0f, // 0.0f, 0.0f,
            1.0f,-1.0f, 1.0f,  // 1.0f, 0.0f, // triangle 7 : end
            1.0f, 1.0f, 1.0f,  // 0.0f, 1.0f, // triangle 8 : begin
            1.0f,-1.0f,-1.0f,  // 1.0f, 0.0f,
            1.0f, 1.0f,-1.0f,  // 1.0f, 1.0f, // triangle 8 : end
            1.0f,-1.0f,-1.0f,  // 1.0f, 0.0f, // triangle 9 : begin
            1.0f, 1.0f, 1.0f,  // 0.0f, 1.0f,
            1.0f,-1.0f, 1.0f,  // 0.0f, 0.0f, // triangle 9 : end
            1.0f, 1.0f, 1.0f,  // 1.0f, 1.0f, // triangle 10 : begin
            1.0f, 1.0f,-1.0f,  // 1.0f, 0.0f,
            -1.0f, 1.0f,-1.0f, // 0.0f, 0.0f, // triangle 10 : end
            1.0f, 1.0f, 1.0f,  // 1.0f, 1.0f, // triangle 11 : begin
            -1.0f, 1.0f,-1.0f, // 0.0f, 0.0f,
            -1.0f, 1.0f, 1.0f, // 0.0f, 1.0f, // triangle 11 : end
            1.0f, 1.0f, 1.0f,  // 1.0f, 1.0f, // triangle 12 : begin
            -1.0f, 1.0f, 1.0f, // 0.0f, 1.0f,
            1.0f,-1.0f, 1.0f   // 1.0f, 0.0f // triangle 12 : end
        },
        m_TexCoords {
               0.0f, 0.0f,
               1.0f, 0.0f,
               1.0f, 1.0f,
               0.0f, 1.0f,
               0.0f, 1.0f,
               1.0f, 1.0f,
               1.0f, 1.0f,
               0.0f, 0.0f,
               1.0f, 0.0f,
               0.0f, 1.0f,
               0.0f, 0.0f,
               1.0f, 0.0f,
               0.0f, 0.0f,
               1.0f, 1.0f,
               0.0f, 1.0f,
               1.0f, 1.0f,
               0.0f, 1.0f,
               0.0f, 0.0f,
               0.0f, 1.0f,
               0.0f, 0.0f,
               1.0f, 0.0f,
               0.0f, 1.0f,
               1.0f, 0.0f,
               1.0f, 1.0f,
               1.0f, 0.0f,
               0.0f, 1.0f,
               0.0f, 0.0f,
               1.0f, 1.0f,
               1.0f, 0.0f,
               0.0f, 0.0f,
               1.0f, 1.0f,
               0.0f, 0.0f, 
               0.0f, 1.0f,
               1.0f, 1.0f,
               0.0f, 1.0f,
               1.0f, 0.0f 
        },
        m_RotationalVelocity(1.0),
        m_va(),
        m_vb(m_Positions, 3 * 36 * sizeof(float)),
        m_vb_texture(m_TexCoords, 2 * 36 * sizeof(float)),
        m_layout(),
        m_layout_texture(),
        m_shader("res/shaders/OrthoTexture.shader"),
        m_renderer(),
        m_camera_pos(glm::vec3(4, 3, -3)),
        m_camera_tgt(glm::vec3(0, 0, 0)),
        m_proj(glm::perspective(glm::quarter_pi<float>(), 4.0f / 3.0f, 0.1f, 100.0f)),
        m_view(glm::lookAt(m_camera_pos, m_camera_tgt, glm::vec3(0, 1, 0))),
        m_model(glm::mat4(1))
    {
        if (!m_BIR.Load("res/textures/marbles.bmp"))
            std::cerr << "Failed to load texture: " << "res/textures/marbles.bmp" << std::endl;

        GLCall( glGenTextures(1, &m_TextureID) );
        GLCall( glBindTexture(GL_TEXTURE_2D, m_TextureID) );
        GLCall( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_BIR.Width(), m_BIR.Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_BIR.Data()) );

        GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
        GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
        GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE) );
        GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE) );

        m_layout.AddFloat(3);
        m_layout_texture.AddFloat(2);
        m_va.AddBuffer(m_vb, m_layout);
        m_va.AddBuffer(m_vb_texture, m_layout_texture, 1);
        m_shader.Bind();
        m_shader.SetUniform1i("u_Texture", 0);

    }

    TestBitmap::~TestBitmap()
    {
        m_shader.Unbind();
    }

    void TestBitmap::OnUpdate(float deltaTime)
    {
        m_model = glm::rotate(
                m_model,
                deltaTime * m_RotationalVelocity,
                glm::vec3(1, 0, 0.5));
    }

    void TestBitmap::OnRender()
    {
        m_renderer.Clear(m_ClearColor);

        m_view = glm::lookAt(m_camera_pos, m_camera_tgt, glm::vec3(0, 1, 0));

        m_shader.Bind();
        m_shader.SetUniformMat4f("u_MVP", m_proj * m_view * m_model);
        m_shader.SetUniform1i("u_Texture", 0);

        // 3 indices starting at 0 -> 1 triangle
        m_renderer.Draw(m_va, m_shader, 36);
    }

    void TestBitmap::OnImGuiRender()
    {
        ImGui::SliderFloat("Rot Vel", &m_RotationalVelocity, 0, 7);
    }
}
