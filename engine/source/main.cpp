#include "window.h"

int main(int argc, char** argv)
{
	Window window(640, 480);
	window.GameLoop();

	(void) argc; (void) argv;
	return 0;
}
