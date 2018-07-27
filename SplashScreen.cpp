#include "StdAfx.h"
#include "SplashScreen.h"

using namespace std;

void SplashScreen::Show(sf::RenderWindow & renderWindow)
{
	sf::Texture splashscreen_image;
	if (splashscreen_image.loadFromFile("Plazma.png") != true)
	{
		return;
	}

	sf::Sprite sprite(splashscreen_image);

	sf::Font font;
	if (!font.loadFromFile("TektonPro-BoldObl.otf"))
	{
		// error...
	}
	sf::Text text;
	text.setFont(font);
	text.setString("Press any key to continue.");
	text.setCharacterSize(24);
	text.setPosition(600, 700);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	sf::Event event;
	sf::Clock gClock;
	bool elapsed = false;
	while (true)
	{
		renderWindow.clear();
		renderWindow.draw(sprite);
		if (elapsed) { 
			renderWindow.draw(text);
		}     
		renderWindow.display();
		if (gClock.getElapsedTime().asSeconds() >= 3.0f) {
			elapsed = true;
		}

		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyPressed
				|| event.type == sf::Event::EventType::MouseButtonPressed
				|| event.type == sf::Event::EventType::Closed)
			{
				
				return;
			}
		}
	}
}