#pragma once

#pragma once

#include <iostream>
#include <string>
#include <glad/glad.h> // or whichever GL loader you use

inline const char* GLErrorToString(GLenum err)
{
	switch (err)
	{
	case GL_NO_ERROR:           return "GL_NO_ERROR";
	case GL_INVALID_ENUM:       return "GL_INVALID_ENUM";
	case GL_INVALID_VALUE:      return "GL_INVALID_VALUE";
	case GL_INVALID_OPERATION:  return "GL_INVALID_OPERATION";
	case GL_OUT_OF_MEMORY:      return "GL_OUT_OF_MEMORY";
	case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
	default:                    return "Unknown Error";
	}
}

inline void glCheckErrorImpl(const char* file, int line, const char* call)
{
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cerr << "[OpenGL Error] (" << GLErrorToString(err) << "): "
			<< call << " in " << file << ":" << line << std::endl;
	}
}

// Macro that wraps a gl call, then checks for errors.
#define GLCheck(x) \
    do { \
        x; \
        glCheckErrorImpl(__FILE__, __LINE__, #x); \
    } while (false)
