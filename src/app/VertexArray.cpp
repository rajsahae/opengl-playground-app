#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, const unsigned int startPos)
{
    Bind();
    vb.Bind();   
    const auto& elements = layout.GetElements();
    unsigned long offset = 0;
    for (int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i + startPos));
        GLCall(glVertexAttribPointer(i + startPos, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }

}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}
