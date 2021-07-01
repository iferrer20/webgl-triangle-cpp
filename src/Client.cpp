#include "Client.h"
#include <cstdio>

std::unique_ptr<Client> client;

Client::Client() {
}

const char* Client::getTargetCanvas() const {
	return "#testgl-canvas";
}

Client::~Client() {}

