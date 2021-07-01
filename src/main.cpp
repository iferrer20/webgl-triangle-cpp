#include <cstdio>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <memory>

#include "Client.h"

#ifdef DEBUG
EM_JS(void, enable_auto_refresh_client, (void), {
	var ws = null;
	function conn() {
		ws = new WebSocket("ws://" + location.hostname + ":8001");
		ws.onmessage = function(m) {
			console.log(m.data);
			location.reload(true);
		};
	}

	conn();
});
#endif

int main(int argc, char **argv) {
#ifdef DEBUG
    enable_auto_refresh_client();
#endif
    client = std::make_unique<Client>();
    return 0;
}
