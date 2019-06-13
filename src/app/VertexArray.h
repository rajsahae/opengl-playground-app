#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
    unsigned int m_RendererID;

public:

    VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, const unsigned int startPos = 0);

    void Bind() const;
    void Unbind() const;
};
