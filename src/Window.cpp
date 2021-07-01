#include "Window.h"
#include <cstdio>
#include <functional>
#include <emscripten/html5.h>
#include <emscripten.h>

#include "Client.h"

Window::Window() {
	double _width, _height;
	emscripten_get_element_css_size("html", &_width, &_height);

	width = _width;
	height = _height;

	emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, true, [] (int, const EmscriptenUiEvent *uiEvent, void *userData) -> EM_BOOL {
		static_cast<Window*>(userData)->onResize(uiEvent->windowInnerWidth, uiEvent->windowInnerHeight);
		return true;
	});

	emscripten_set_canvas_element_size(client->getTargetCanvas(), width, height);

	setTitle("testgl");
}

Window::~Window() {

}

void Window::onResize(int new_width, int new_height) {
	width = new_width;
	height = new_height;
	emscripten_set_canvas_element_size(client->getTargetCanvas(), width, height);
}

void Window::setTitle(std::string_view new_title) {
	title = new_title;
	emscripten_set_window_title(title.c_str());
}

std::string_view Window::getTitle() const {
	return title;
}

int Window::getWidth() const {
	return width;
}

int Window::getHeight() const {
	return height;
}
