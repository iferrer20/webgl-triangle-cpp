#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

class Triangle {

public:
	Triangle();
	virtual ~Triangle();
	void render();
	GLuint program;
	GLuint vertexbuffer;
};
