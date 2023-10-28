#include "bird.h"

void bird::setup() {
	if (!bird_frames[0].loadFromFile("img/bird0.png")) {
		std::cout << "Error while loading bird frame0!" << std::endl;
	}
	if (!bird_frames[1].loadFromFile("img/bird1.png")) {
		std::cout << "Error while loading bird frame1!" << std::endl;
	}
	if (!bird_frames[2].loadFromFile("img/bird2.png")) {
		std::cout << "Error while loading bird frame2!" << std::endl;
	}
	bird_sprite.setTexture(bird_frames[0]);
	bird_sprite.setPosition(10.f, 300.f);
	bird_sprite.setScale(0.2, 0.2);
	BirdHeight = bird_frames[0].getSize().y * bird_sprite.getScale().y;
	BirdWidth = bird_frames[0].getSize().x * bird_sprite.getScale().x - 10;
	isMoving = true;
	isDead = false;
	pointgain = false;
	velocity = 0.f;
	cur_frame = 0.f;
}

sf::Sprite& bird::getSprite() {
	return bird_sprite;
}

float bird::get_X_position() {
	return bird_sprite.getPosition().x;
}

float bird::get_Y_position() {
	return bird_sprite.getPosition().y;
}

float bird::getWidth() {
	return BirdWidth;
}

float bird::getHeight() {
	return BirdHeight;
}

float bird::getVelocity() {
	return velocity;
}

void bird::setVelocity(float updated_velocity) {
	velocity = updated_velocity;
}

bool bird::getMovState() {
	return isMoving;
}

void bird::setMovState(bool MovState) {
	isMoving = MovState;
}

bool bird::getDeadState() {
	return isDead;
}

void bird::setDeadState(bool DeadState) {
	isDead = DeadState;
}

bool bird::getPointState() {
	return pointgain;
}

void bird::setPointState(bool state) {
	pointgain = state;
}

void bird::animation(float dt) {
	cur_frame += 0.005 * dt;
	if (cur_frame > 3) cur_frame -= 3;
	if (cur_frame < 1) bird_sprite.setTexture(bird_frames[0]);
	else if (cur_frame < 2) bird_sprite.setTexture(bird_frames[1]);
	else bird_sprite.setTexture(bird_frames[2]);
}

void bird::setPos(float x, float y) {
	bird_sprite.setPosition(x, y);
}

void bird::updateVelocity(float expression) {
	velocity += expression;
}

void bird::Jump(float dt) {
	velocity = 0;
	velocity -= velocity_kick * dt;
}

void bird::Move() {
	if (isMoving) {
		bird_sprite.move(0.f, velocity);
	}
}