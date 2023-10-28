#pragma once
#include "PHH.h"

const int frames_size = 3;

class bird
{
private:
	sf::Texture bird_frames[frames_size];
	sf::Sprite bird_sprite;
	float BirdHeight;
	float BirdWidth;
	bool isMoving;
	bool isDead;
	bool pointgain;
	float velocity;
	const float velocity_kick = 0.2;
	float cur_frame;
public:
	void setup();
	sf::Sprite& getSprite();
	float get_X_position();
	float get_Y_position();
	float getWidth();
	float getHeight();
	float getVelocity();
	void setVelocity(float);
	bool getMovState();
	void setMovState(bool);
	bool getDeadState();
	void setDeadState(bool);
	bool getPointState();
	void setPointState(bool);
	void animation(float);
	void setPos(float, float);
	void updateVelocity(float);
	void Jump(float);
	void Move();
};