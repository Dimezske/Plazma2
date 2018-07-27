#include "Objects.h"
#include "Game.h"
#include "GameObjectManager.h"
int Trees::TreeCount;
Trees::Trees() {
	oTexture.loadFromFile("pinetree.png");
	for (int i = 0; i < 30; ++i) {
		oSprite[i].setTexture(oTexture);
	}
}

Trees::~Trees() {
}

void Trees::Draw(sf::RenderWindow & windowz)
{
	for (int i = 0; i < 30; ++i)
	{
		
		windowz.draw(oSprite[i]);
	}
}

sf::Vector2f Trees::getRandomPosition(std::size_t x_range, std::size_t y_range)
{
	return sf::Vector2f(rand() % x_range, rand() % y_range);
}
void Trees::GenerateTrees() {
	
	for (int i = 0; i < 30; ++i)
	{
		
			oSprite[i].setPosition(getRandomPosition(1500, 1500));
	}
}
