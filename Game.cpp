#include "Game.h"

// Private functions
void Game::initVariables() 
{
	m_pWindow = nullptr;

	// Game logic
	m_EndGame = false;
	m_Points = 0;
	m_Health = 10;
	m_EnemySpawnTimerMax = 15.f;
	m_EnemySpawnTimer = m_EnemySpawnTimerMax;
	m_MaxEnemies = 6;
	m_MouseHeld = false;
}

void Game::initWindow() 
{
	m_videoMode.height = 600;
	m_videoMode.width = 800;

	m_pWindow = new RenderWindow(m_videoMode, "AimTraining", Style::Titlebar | Style::Close);

	m_pWindow->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (!m_Font.loadFromFile("../Fonts/Aqua_Smile.ttf")){
		cout << "ERROR: Game::initFonts() - Failed to load font.\n";
	}
}

void Game::initText()
{
	// Points
	m_uiTextPoints.setFont(m_Font);
	m_uiTextPoints.setCharacterSize(16);
	m_uiTextPoints.setFillColor(Color::White);
	m_uiTextPoints.setString("NONE");
	m_uiTextPoints.setPosition(20.f, 20.f);

	// Health
	m_uiTextHealth.setFont(m_Font);
	m_uiTextHealth.setCharacterSize(16);
	m_uiTextHealth.setFillColor(Color::White);
	m_uiTextHealth.setString("NONE");
	m_uiTextHealth.setPosition(660.f, 20.f);
}

void Game::initEnemies() {
	m_Enemy.setPosition(10.f, 10.f);
	m_Enemy.setSize(Vector2f(100.f, 100.f));
	m_Enemy.setFillColor(Color::Cyan);
}

// Constructors / Destructors
Game::Game() {
	initVariables();
	initWindow();
	initFonts();
	initText();
	initEnemies();
}

Game::~Game() {
	delete m_pWindow;
	m_pWindow = nullptr;
}

// Accessors
const bool Game::getWindowIsOpen() const {
	return m_pWindow->isOpen();
}

const bool Game::getEndGame() const {
	return m_EndGame;
}

// Functions
void Game::spawnEnemy() {
	/*
		Spawn enemies and sets their color and positions.
			- Sets a random positions.
			- Sets a random color.
			- Adds enemy to the vector.
	*/

	m_Enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(m_pWindow->getSize().x - m_Enemy.getSize().x)),
		0.f
	);

	// Randomize color
	int random = rand() % 8;
	if (random == 0) {
		m_Enemy.setFillColor(Color::Red);
		m_Enemy.setSize(Vector2f(18.f, 18.f));
	}
	else if (random == 1) {
		m_Enemy.setFillColor(Color::Cyan);
		m_Enemy.setSize(Vector2f(25.f, 25.f));
	}
	else {
		m_Enemy.setFillColor(Color::Green);
		m_Enemy.setSize(Vector2f(45.f, 45.f));
	}

	// Spawn enemies
	m_Enemies.push_back(m_Enemy);
}

void Game::pollEvents() {
	while (m_pWindow->pollEvent(m_ev)) {
		if (m_ev.type == Event::Closed) {
			m_pWindow->close();
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
		m_pWindow->close();
	}
}

void Game::updateMousePosition() {
	m_MousePosWindow = Mouse::getPosition(*m_pWindow);
	m_MousePosView = m_pWindow->mapPixelToCoords(m_MousePosWindow);
}

void Game::updateText()
{
	// Points
	stringstream ss;
	ss << "Points: " << m_Points;
	m_uiTextPoints.setString(ss.str());

	// Health
	stringstream sss;
	sss << "Health: " << m_Health;
	m_uiTextHealth.setString(sss.str());
}

void Game::updateEnemies() {
	// Updating the timer for enemy spawning
	if (m_Enemies.size() < m_MaxEnemies) {
		if (m_EnemySpawnTimer >= m_EnemySpawnTimerMax) {
			// Spawn enemy and reset the timer
			spawnEnemy();
			m_EnemySpawnTimer = 0.f;
		}
		else {
			m_EnemySpawnTimer += 1.f;
		}
	}

	// Moving and updating enemies
	for (int i = 0; i < m_Enemies.size(); i++) {
		bool deleted = false;

		m_Enemies[i].move(0.f, 2.f);

		if (m_Enemies[i].getPosition().y > m_pWindow->getSize().y) {
			m_Enemies.erase(m_Enemies.begin() + i);
			m_Health -= 1;
		}
	}
	
	// Check if clicked
	if (Mouse::isButtonPressed(Mouse::Left)) {

		if (m_MouseHeld == false) {

			m_MouseHeld = true;
			bool deleted = false;

			for (int i = 0; i < m_Enemies.size() && deleted == false; i++) {
				if (m_Enemies[i].getGlobalBounds().contains(m_MousePosView)) {
					deleted = true;

					// Check color enemies
					if (m_Enemies[i].getFillColor() == Color::Red)
					{
						m_Points += 5;
					}

					if (m_Enemies[i].getFillColor() == Color::Cyan)
					{
						m_Points += 3;
					}

					else {
						m_Points += 1;
					}

					// Deleting enemies
					m_Enemies.erase(m_Enemies.begin() + i);
				}
			}
		}
	}
	else {
		m_MouseHeld = false;
	}
}

void Game::update() {
	pollEvents();

	if (!m_EndGame) {
		updateMousePosition();

		updateText();

		updateEnemies();
	}

	// End game
	if (m_Health <= 0) {
		m_EndGame = true;
	}
}

void Game::renderText(RenderTarget& target)
{
	target.draw(m_uiTextPoints);
	target.draw(m_uiTextHealth);
}

void Game::renderEnemies(RenderTarget& target) {
	// Rendering all the enemies
	for (auto& e : m_Enemies) {
		target.draw(e);
	}
}

void Game::render() {
	// Renders the game objects

	m_pWindow->clear();

	// Draw game objects
	renderEnemies(*m_pWindow);

	renderText(*m_pWindow);

	m_pWindow->display();
}