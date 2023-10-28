#pragma once
#include "PHH.h"
class sounds
{
private:
	sf::SoundBuffer buffer[3];
	sf::Sound sound[3];
public:
	sounds();
	void point_sound();
	void wing_sound();
	void hit_sound();
};

