#include "gameengine.h"
int main()
{
	gameengine Gameengine;
	while (Gameengine.running()) {
		Gameengine.update();
		Gameengine.render();
	}
	return 0;
}
