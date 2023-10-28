#pragma once
#include "PHH.h"
#include "sounds.h"
#include "game_object.h"
#include "bird.h"

class gameengine
{
private:
	sf::Font font;
	sf::Text text_points;
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Clock clock;
	sf::Event event;
	sf::Texture tubetexture;
	sf::Sprite bottomtube[2];
	sf::Sprite uppertube[2];
	game_object overlay;
	game_object restart_button;
	game_object pause_button;
	game_object background;
	sounds game_sounds;
	bird Bird_player;
	float dt;
	float ground_velocity;
	float acceleration_of_gravity;
	float TubeWidth;
	int points;
	bool isPaused;
	sf::Texture groundtexture;
	sf::Sprite groundsprite[2];
	void InitVar();
	void InitWindow();
	void InitTube();
	void InitFont();
public:
	gameengine();
	virtual ~gameengine();
	bool running();
	void gameover();
	void physics();
	void physics_kick();
	void collision();
	void update_objects();
	void fontupdate();
	void updatepooling();
	void update();
	void render();
};