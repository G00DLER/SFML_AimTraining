#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;

/*
	Class that acts as the game engine.
	Wrapper class.
*/

class Game
{
private:
	// Variables
	// Window
	RenderWindow* m_pWindow;
	Event m_ev;
	VideoMode m_videoMode;

	// Mouse positions
	Vector2i m_MousePosWindow;
	Vector2f m_MousePosView;

	// Resources
	Font m_Font;

	// Text
	Text m_uiTextPoints;
	Text m_uiTextHealth;

	// Game logic
	bool m_EndGame;
	unsigned m_Points;
	int m_Health;
	float m_EnemySpawnTimer;
	float m_EnemySpawnTimerMax;
	int m_MaxEnemies;
	bool m_MouseHeld;

	// Game objects
	vector<RectangleShape> m_Enemies;
	RectangleShape m_Enemy;

	// Private functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initEnemies();
public:
	// Constructors / Destructors
	Game();
	virtual ~Game();

	// Accessors
	const bool getWindowIsOpen() const;
	const bool getEndGame() const;

	// Functions
	void spawnEnemy();

	void pollEvents();
	void updateMousePosition();
	void updateText();
	void updateEnemies();
	void update();

	void renderText(RenderTarget& target);
	void renderEnemies(RenderTarget& target);
	void render();
};

#endif