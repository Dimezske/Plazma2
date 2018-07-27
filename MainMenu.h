#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include <list>

class MainMenu
{

public:
	enum MenuResult { Nothing, Exit, Play };

	struct MenuItem
	{
	public:
		sf::Rect<int> area;
		MenuResult action;
		
		sf::Texture splashimg;
		sf::Sprite mSplash;

		sf::Texture start_button;
		sf::Sprite mIconSprite;
		
	};
	MenuResult Show(sf::RenderWindow& window);
private:
	

	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
	std::list<MenuItem> _menuItems;
};
