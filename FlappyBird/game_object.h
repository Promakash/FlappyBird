#pragma once
#include "PHH.h"
class game_object
{
protected:
	sf::Texture game_object_texture;
	sf::Sprite game_object_sprite;
public:
	void setup(std::string);
	void setPos(float, float);
	sf::Sprite& getSprite();
};
