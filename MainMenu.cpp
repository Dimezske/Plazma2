#include "stdafx.h"
#include "MainMenu.h"
#include "Game.h"
#include "ServiceLocator.h"
MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{

	//Load menu image from file
	//start_button.loadFromFile("startbuttonj.png");
	//sf::Sprite mStartButton(start_button);
	
	//Setup clickable regions
	
	
	MenuItem splashScreen;
	splashScreen.splashimg.loadFromFile("Plazma.png");
	splashScreen.mSplash.setTexture(splashScreen.splashimg);
	
	//Play menu item coordinates
	MenuItem playButton;
	playButton.start_button.loadFromFile("startbuttonj.png");
	playButton.mIconSprite.setTexture(playButton.start_button);
	
	
	sf::IntRect playBtn_pos(500, 500, 280, 69);
	playButton.area = playBtn_pos;
	playButton.action = Play;
	playButton.mIconSprite.setPosition(playBtn_pos.left, playBtn_pos.top);
	/*
	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect.left = 0;
	exitButton.rect.width = 1023 - 0;
	exitButton.rect.top = 383;
	exitButton.rect.height = 383 - 145;
	exitButton.action = Exit;
	*/
	//_menuItems.emplace_back(splashScreen);
	_menuItems.emplace_back(playButton);
	
	window.draw(splashScreen.mSplash);
	window.draw(playButton.mIconSprite);
	window.display();

	return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).area;
		if ((menuItemRect.top + menuItemRect.height) > y &&
			menuItemRect.top < y &&
			menuItemRect.left < x &&
			(menuItemRect.left + menuItemRect.width) > x)
		{
			return (*it).action;
		}
	}

	return Nothing;
}

MainMenu::MenuResult  MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while (42 != 43)
	{

		while (window.pollEvent(menuEvent))
		{
			//if (menuEvent.type == sf::Event::Closed) _gameState = Game::Exiting;

			if (menuEvent.type == sf::Event::MouseButtonPressed)
			{
				if (ServiceLocator::GetAudio()->IsSongPlaying())
					ServiceLocator::GetAudio()->StopAllSounds();

				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}
			if (menuEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}
	}
}