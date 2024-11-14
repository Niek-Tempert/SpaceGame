#include "program.h"

int main() {
	Program *program;

	start(&program);
	update(program);
	cleanup(program);
}