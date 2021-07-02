#include <cstdio>
#include <emscripten/html5.h>
#include <emscripten.h>
#include <emscripten/emscripten.h>
#include <assert.h>
#include <GLES2/gl2.h>


#include "Render.h"
#include "Client.h"
#include "Triangle.h"

static void doLoop(void*);

std::unique_ptr<Triangle> t;

Render::Render() {
	EmscriptenWebGLContextAttributes attrV1;
	EmscriptenWebGLContextAttributes attrV2;
	attrV2.majorVersion = 2;

	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx =
			emscripten_webgl_create_context(client->getTargetCanvas(), &attrV2) ||
			emscripten_webgl_create_context(client->getTargetCanvas(), &attrV1);

	assert(ctx);

	EMSCRIPTEN_RESULT r = emscripten_webgl_make_context_current(ctx);
	assert(r == EMSCRIPTEN_RESULT_SUCCESS);

	r = emscripten_webgl_make_context_current(ctx);
	assert(r == EMSCRIPTEN_RESULT_SUCCESS);

	emscripten_webgl_enable_OES_vertex_array_object(ctx);
	emscripten_webgl_enable_WEBGL_draw_buffers(ctx);
	emscripten_webgl_enable_WEBGL_multi_draw(ctx);
	emscripten_webgl_enable_ANGLE_instanced_arrays(ctx);

	t = std::make_unique<Triangle>();

	emscripten_set_main_loop_arg(doLoop, this, 0, false);

}
Render::~Render() {}

static void doLoop(void *u) {
	static_cast<Render*>(u)->loop();
}

void Render::loop() {
	// main render loop
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, client->window.getWidth(), client->window.getHeight());
	t->render();

}




