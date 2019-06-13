#pragma once

#include "Debug.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
private:

public:

    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Draw(const VertexArray& va, const Shader& shader, const int numVertices, const int startPos = 0) const;
    void Clear() const;
    void Clear(float clearColor[4]) const;
};
