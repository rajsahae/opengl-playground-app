#include "Renderer.h"

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

}

void Renderer::Clear(float clearColor[4]) const
{
    Clear();
    if (clearColor)
    {
        GLCall(glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]));
    }
    else
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    }
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    /* draw a triangle with modern opengl */
    GLCall( glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr) );
}

void Renderer::Draw(const VertexArray& va, const Shader& shader, const int numVertices, const int startPos) const
{
    shader.Bind();
    va.Bind();

    /* draw a triangle with modern opengl */
    GLCall( glDrawArrays(GL_TRIANGLES, startPos, numVertices) );
}
