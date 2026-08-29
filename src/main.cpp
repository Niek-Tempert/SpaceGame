#include "spacegame.h"

int main() {
	Engine engine;

	start(&engine);
	update(&engine);
	cleanup(&engine);
}
