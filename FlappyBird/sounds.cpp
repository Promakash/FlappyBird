#include "sounds.h"

sounds::sounds() {
	if (!buffer[0].loadFromFile("sounds/sfx_point.wav")) {
		std::cout << "Error while loading sfx_point!" << std::endl;
	}
	sound[0].setBuffer(buffer[0]);
	if (!buffer[1].loadFromFile("sounds/sfx_wing.wav")) {
		std::cout << "Error while loading sfx_wing!" << std::endl;
	}
	sound[1].setBuffer(buffer[1]);
	if (!buffer[2].loadFromFile("sounds/sfx_hit.wav")) {
		std::cout << "Error while loading sfx_die.wav" << std::endl;
	}
	sound[2].setBuffer(buffer[2]);
}
void sounds::point_sound() {
	sound[0].play();
}
void sounds::wing_sound() {
	sound[1].play();
}
void sounds::hit_sound() {
	sound[2].play();
}