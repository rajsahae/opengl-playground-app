#pragma once

#include <cassert>
#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define GLCall(x) \
        GLClearError(); \
        x; \
        assert(GLLogCall())

void GLClearError();
bool GLLogCall();

class Renderer
{
private:

public:

    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;
};
