#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Paddle.h"
#include "GameObjectManager.h"
#include "GameBall.h"

class Game
{

public:
	static void Start();
	static sf::RenderWindow& GetWindow();
	const static sf::Event& GetInput();
	const static GameObjectManager& GetGameObjectManager();
	
	const static int WINDOW_WIDTH = 1400;
	const static int WINDOW_HEIGHT = 800;

	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting
	};

private:
	sf::Clock mTimer;

	static bool IsExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowMenu();

	static bool SetDefaultTiles();

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;

	static GameObjectManager _gameObjectManager;
};

