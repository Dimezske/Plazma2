#pragma once
#include "VisibleGameObject.h"
#include "Game.h"
class Player : public VisibleGameObject
{
public:
	Player();
	~Player();
	
	void Update(float elapsedTimer);
	void Draw(sf::RenderWindow &renderWindow);

	void Dir(int dir);
	//void playerMovement(sf::RenderWindow & renderWindow);
	
	float GetVelocity() const;
	sf::Clock frameClock;
	void playerAnimation_WalkDown();
	void playerAnimation_WalkUp();
	void playerAnimation_WalkLeft();
	void playerAnimation_WalkRight();
protected:
	enum PlayerControlState {
		Walking, Idle, Running
		//-NOTE add item use and weapon use
	};

private:
	bool mMoving = false;
	float _velocity;  // -- left ++ right
	float _maxVelocity;
	sf::Clock mClock;
	sf::Time mTime;
	sf::Clock mClock2;
	sf::Time mTime2;
	//sf::Sprite mSprite;
	sf::Event playerEvent;
	static PlayerControlState _playerControls;
};