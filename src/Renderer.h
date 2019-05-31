#pragma once

#include <cassert>
#include <GL/glew.h>

#define GLCall(x) \
        GLClearError(); \
        x; \
        assert(GLLogCall())

void GLClearError();
bool GLLogCall();
