#include "game_object.h"
void game_object::setup(std::string path) {
	if (!game_object_texture.loadFromFile(path)) {
		std::cout << "Error while loading pause button texture!" << std::endl;
	}
	game_object_sprite.setTexture(game_object_texture);
}
void game_object::setPos(float x, float y) {
	game_object_sprite.setPosition(x, y);
}
sf::Sprite& game_object::getSprite() {
	return game_object_sprite;
}