#include "Triangle.h"

#include <cstdio>
#include <initializer_list>
#include <exception>

static constexpr GLfloat triangleVertices[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f
};
static const GLchar* glVertexShader = R"(
attribute vec3 vPosition;
void main() {
	gl_Position = vec4(vPosition, 1.0);
}
)";

static const GLchar* glFragmentShader = R"(
precision mediump float;
void main() {
  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
)";


Triangle::Triangle() {

	// Load vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    {
    	glShaderSource(vertexShader, 1, &glVertexShader, nullptr);
		glCompileShader(vertexShader);
		GLint compiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			GLint infoLen = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLen);
			char buf[infoLen];
			glGetShaderInfoLog(vertexShader, infoLen, nullptr, buf);
			std::printf("Could not Compile Shader %s:\n", buf);
			glDeleteShader(vertexShader);
			vertexShader = 0;
			std::terminate();
		}
    }

	// Load fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    {
    	glShaderSource(fragmentShader, 1, &glFragmentShader, nullptr);
		glCompileShader(fragmentShader);
		GLint compiled = 0;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			GLint infoLen = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLen);
			char buf[infoLen];
			glGetShaderInfoLog(fragmentShader, infoLen, nullptr, buf);
			std::printf("Could not Compile Shader %s:\n", buf);
			glDeleteShader(fragmentShader);
			fragmentShader = 0;
			std::terminate();
		}

    }

	// Create program
	program = glCreateProgram();
	glAttachShader(program , vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLint linkStatus = GL_FALSE;
	glGetProgramiv(program , GL_LINK_STATUS, &linkStatus);
	if(linkStatus != GL_TRUE)
	{
		GLint bufLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
		char buf[bufLength];
		glGetProgramInfoLog(program, bufLength, NULL, buf);
		std::printf("Could not create shader Program %s:\n", buf);
		glDeleteProgram(program);
		program = 0;
	}

	// This will identify our vertex buffer
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);


	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);

	glVertexAttribPointer(
	   vPosition,
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);


}

Triangle::~Triangle() {
	// TODO Auto-generated destructor stub
}

void Triangle::render() {
	glUseProgram(program);
	glBindVertexArrayOES(vertexbuffer);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUseProgram(0);
}
