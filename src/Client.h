#pragma once
#include <memory>

#include "Render.h"
#include "Window.h"


class Client {
public:
	Window window;
	Render render;

	Client();
	const char* getTargetCanvas() const;

	void run();
	virtual ~Client();
};

extern std::unique_ptr<Client> client;
