#include "gameengine.h"


const std::string path_to_overlay = "img/overlay.png";
const std::string path_to_restart_button = "img/restart.png";
const std::string path_to_pause_button = "img/pause.png";
const std::string path_to_background = "img/background.png";
const std::string path_to_bird_texture = "img/ground.png";
const float window_height = 700.f;
const float window_width = 400.f;
const int framerate = 60;


//TODO: Scoreboard, menu, add speed while some points.
void gameengine::InitVar()
{
	srand(time(0));
	dt = 0.f;
	acceleration_of_gravity = 0.0025;
	ground_velocity = 1.5;
	TubeWidth = 0.f;
	points = 0;
	isPaused = false;
}

void gameengine::InitWindow()
{
	videoMode.height = window_height;
	videoMode.width = window_width;
	window = new sf::RenderWindow(videoMode, "Flappy SUAI!", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(framerate);
	window->setKeyRepeatEnabled(false);
	background.setup(path_to_background);
	if (!groundtexture.loadFromFile("img/ground.png")) {
		std::cout << "Error while loading ground texture!" << std::endl;
	}
	groundsprite[0].setPosition(0.f, 620.f);
	groundsprite[1].setPosition(497.f, 620.f);
	groundsprite[0].setTexture(groundtexture);
	groundsprite[1].setTexture(groundtexture);
	pause_button.setup(path_to_pause_button);
	overlay.setup(path_to_overlay);
	restart_button.setup(path_to_restart_button);
	restart_button.setPos(350.f, 0.f);
}

void gameengine::InitTube()
{
	int y_pos_tube = 0;
	float x_pos_tube = 300.f;
	if (!tubetexture.loadFromFile("img/tube.png")) {
		std::cout << "Error while loading tube texture";
	}
	for (int i = 0; i < 2; i++) {
		y_pos_tube = 60 + rand() % (350 - 60 + 1);
		uppertube[i].setTexture(tubetexture);
		uppertube[i].setPosition(x_pos_tube, y_pos_tube);
		uppertube[i].setScale(sf::Vector2f(0.3, -0.5));
		bottomtube[i].setTexture(tubetexture);
		bottomtube[i].setPosition(x_pos_tube, y_pos_tube + 160.f);
		bottomtube[i].setScale(sf::Vector2f(0.3, 0.5));
		x_pos_tube += 300.f;
	}
	TubeWidth = tubetexture.getSize().x * 0.3 + 20;
}

void gameengine::InitFont()
{
	if (!font.loadFromFile("FlappyBirdRegular.ttf")) {
		std::cout << "Error while loading font!" << std::endl;
	}
	text_points.setFont(font);
	text_points.setFillColor(sf::Color::White);
	text_points.setString("0");
	text_points.setCharacterSize(72);
}

gameengine::gameengine()
{
	InitVar();
	InitWindow();
	InitTube();
	Bird_player.setup();
	InitFont();
}

gameengine::~gameengine()
{
	delete window;
}

bool gameengine::running()
{
	return window->isOpen();
}

void gameengine::gameover()
{
	if (!Bird_player.getDeadState()) game_sounds.hit_sound();
	ground_velocity = 0;
	Bird_player.setDeadState(true);
}

void gameengine::physics()
{
	if (!isPaused) Bird_player.updateVelocity(dt * acceleration_of_gravity);
}

void gameengine::physics_kick()
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && Bird_player.getVelocity() > 0.5) {
		Bird_player.Jump(dt);
		game_sounds.wing_sound();
	}
}

void gameengine::collision()
{
	float x_pos = Bird_player.get_X_position();
	float y_pos = Bird_player.get_Y_position();
	float birdHeight = Bird_player.getHeight();
	float birdWidth = Bird_player.getWidth();
	if (y_pos < 0) {
		gameover();
		Bird_player.setVelocity(0.f);
		Bird_player.setPos(x_pos, 0.f);
	}
	if (y_pos+birdHeight >= 620 && Bird_player.getMovState()) {
		gameover();
		Bird_player.setMovState(false);
	}
	for (int i = 0; i < 2; i++) {
		if (!Bird_player.getDeadState() && x_pos + birdWidth >= bottomtube[i].getPosition().x && x_pos + birdWidth <= bottomtube[i].getPosition().x + TubeWidth && (y_pos + birdHeight >= bottomtube[i].getPosition().y + 10 || y_pos <= uppertube[i].getPosition().y - 10)) {
			gameover();
		}
		if (!Bird_player.getPointState() && (x_pos >= bottomtube[i].getPosition().x && x_pos <= bottomtube[i].getPosition().x + TubeWidth) && (y_pos >= uppertube[i].getPosition().y && y_pos <= bottomtube[i].getPosition().y)) {
			game_sounds.point_sound();
			Bird_player.setPointState(true);
			points += 1;
			text_points.setString(std::to_string(points));
		}
		else if (x_pos >= bottomtube[i].getPosition().x + TubeWidth) Bird_player.setPointState(false);
	}
}

void gameengine::update_objects()
{
	Bird_player.Move();
	for (int i = 0; i < 2; i++) {
		groundsprite[i].move(sf::Vector2f(-(ground_velocity), 0.f));
		if (groundsprite[i].getPosition().x < -497.f) {
			groundsprite[i].setPosition(497.f, groundsprite[i].getPosition().y);
		}
		bottomtube[i].move(sf::Vector2f(-(ground_velocity), 0.f));
		uppertube[i].move(sf::Vector2f(-(ground_velocity), 0.f));
		if (uppertube[i].getPosition().x < -100.f) {
			uppertube[i].setPosition(500.f, 60 + rand() % (350 - 60 + 1));
			bottomtube[i].setPosition(500.f, uppertube[i].getPosition().y + 160.f);
		}
	}
}

void gameengine::fontupdate()
{
	text_points.setPosition(400.f / 2 - text_points.getLocalBounds().width / 2, 620.f);
}

void gameengine::updatepooling()
{
	dt = (float)clock.getElapsedTime().asMilliseconds();
	clock.restart();
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window->close();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(*window).x >= 0 && sf::Mouse::getPosition(*window).x <= 50 && 
			sf::Mouse::getPosition(*window).y >= 0 && sf::Mouse::getPosition(*window).y <= 50 && !isPaused && !Bird_player.getDeadState()) {
			isPaused = true;
		}
		if (isPaused && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			isPaused = false;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(*window).x >= 350 && sf::Mouse::getPosition(*window).x <= 400 &&
			sf::Mouse::getPosition(*window).y >= 0 && sf::Mouse::getPosition(*window).y <= 50) {
			InitVar();
			InitTube();
			Bird_player.setup();
			InitFont();
		}
		if (!Bird_player.getDeadState() && !isPaused) physics_kick();
	}
}

void gameengine::update()
{
	fontupdate();
	physics();
	updatepooling();
	if (!isPaused) {
		update_objects();
		if (!Bird_player.getDeadState()) Bird_player.animation(dt);
		collision();
	}
}

void gameengine::render()
{
	window->clear();
	window->draw(background.getSprite());
	for (int i = 0; i < 2; i++) {
		window->draw(uppertube[i]);
		window->draw(bottomtube[i]);
	}
	for (int i = 0; i < 2; i++) {
		window->draw(groundsprite[i]);
	}
	window->draw(Bird_player.getSprite());
	window->draw(text_points);
	if (isPaused) {
		window->draw(overlay.getSprite());
	}
	window->draw(pause_button.getSprite());
	window->draw(restart_button.getSprite());
	window->display();
}