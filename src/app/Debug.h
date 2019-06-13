#pragma once

#include <iostream>
#include <cassert>
#include <GL/glew.h>

/*
 * We make the header-only debug functions inline to avoid duplicate symbols during linkage
 */

void inline GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool inline GLLogCall() {
    while( GLenum error = glGetError() )
    {
        std::string msg;

        switch(error)
        {
            case GL_NO_ERROR:
                return true;
            case GL_INVALID_ENUM:
                msg = "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument";
                break;
            case GL_INVALID_VALUE:
                msg = "GL_INVALID_VALUE: A numeric argument is out of range";
                break;
            case GL_INVALID_OPERATION:
                msg = "GL_INVALID_OPERATION: The specified operation is not allowed in the current state";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                msg = "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete";
                break;
            case GL_OUT_OF_MEMORY:
                msg = "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command";
                break;
            case GL_STACK_UNDERFLOW:
                msg = "GL_STACK_UNDERFLOW: An attempt has been made to perform an operation that would cause an internal stack to underflow.";
                break;
            case GL_STACK_OVERFLOW:
                msg = "GL_STACK_OVERFLOW: An attempt has been made to perform an operation that would cause an internal stack to overflow.";
                break;
            default:
                msg = "An unknown error was encountered";
                break;
        }

        std::cout << "[OpenGL Error] (" << error << ")" << " " << msg << std::endl;
        return false;
    }
    return true;
}

#define GLCall(x) \
        GLClearError(); \
        x; \
        assert(GLLogCall())

