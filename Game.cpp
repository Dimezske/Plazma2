#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "Tilemap.h"
#include "Tilemapping.h"
#include "Player.h"
#include "ServiceLocator.h"
#include "SFMLSoundProvider.h"
#include "ServiceLocator.h"
#include "Objects.h"
int level[100][100] = {};

void Game::Start(void)
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Plazma");
	
	//_mainWindow.SetFramerateLimit(60);

	SFMLSoundProvider soundProvider;
	ServiceLocator::RegisterServiceLocator(&soundProvider);

	soundProvider.PlaySong("Plazmasplashsounds.ogg", true);
	
	_gameState = Game::ShowingSplash;

	Player *player = new Player();
	player->SetPosition((WINDOW_WIDTH / 2) - 45, 400);
	_gameObjectManager.Add("Player", player);


	// Objects
	Trees * trees = new Trees();
	trees->GenerateTrees();
	_gameObjectManager.Add("BigFolage", trees);

	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

bool Game::IsExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}
sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

const sf::Event& Game::GetInput()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	return currentEvent;
}
const GameObjectManager& Game::GetGameObjectManager()
{
	return Game::_gameObjectManager;
}
void Game::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);


	switch (_gameState)
	{
	case Game::ShowingMenu:
	{
		ShowMenu();
		break;
	}
	case Game::ShowingSplash:
	{
		ShowSplashScreen();
		break;
	}
	case Game::Playing:
	{
		_mainWindow.clear(sf::Color(14, 17, 15));
		SetDefaultTiles();
		_gameObjectManager.UpdateAll();
		_gameObjectManager.DrawAll(_mainWindow);
		
		
		sf::View view(sf::FloatRect(0, 0, Game::GetWindow().getSize().x, Game::GetWindow().getSize().y));
		view.reset(sf::FloatRect(0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT));
		view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
		view.setCenter(sf::Vector2f(50, 50));
		view.setCenter(_gameObjectManager.Get("Player")->GetPosition());
		Game::GetWindow().setView(view);
		
		_mainWindow.display();
		if (currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;

		if (currentEvent.type == sf::Event::KeyPressed)
		{
			if (currentEvent.key.code == sf::Keyboard::Escape) ShowMenu();
		}
		break;
	}
  }
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch (result)
	{
	case MainMenu::Exit:
		_gameState = Game::Exiting;
		break;
	case MainMenu::Play:
		_gameState = Game::Playing;
		break;
	}
}
bool Game::SetDefaultTiles()
{
	TileMap tileset;
	if (!tileset.load("grass1.png", sf::Vector2u(16, 16), level, 100, 100))
	{
		return -1;
	}
	_mainWindow.draw(tileset);
	if (level[7] == level[7])
	{
		//soundBuffer2.loadFromFile("");
		//sound2.setBuffer(soundBuffer2);
	}
}

// A quirk of C++, static member variables need to be instantiated outside of the class
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
