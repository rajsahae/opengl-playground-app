#pragma once

#include <vector>
#include <GL/glew.h>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch(type)
        {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        assert(false);
        return 0;
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    int m_Stride;

public:
    VertexBufferLayout() : m_Stride(0) {}

    void AddFloat(unsigned int count)
    {
        m_Elements.push_back({GL_FLOAT, count, false});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    void AddInt(unsigned int count)
    {
        m_Elements.push_back({GL_UNSIGNED_INT, count, false});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    void AddChar(unsigned int count)
    {
        m_Elements.push_back({GL_UNSIGNED_BYTE, count, true});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
    inline const unsigned int GetStride() const { return m_Stride; }
};
