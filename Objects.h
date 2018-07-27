#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "stdafx.h"
#include "VisibleGameObject.h"

class Trees : public VisibleGameObject{
public:
	Trees();
	~Trees();
	
	static int TreeCount;
	void Draw(sf::RenderWindow & window);
	sf::Vector2f getRandomPosition(std::size_t x_range, std::size_t y_range);
    void GenerateTrees();
private:
	sf::Texture oTexture;
	sf::Sprite oSprite[30];
};