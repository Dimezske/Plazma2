#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "GameObjectManager.h"
#include <iostream>

using namespace std;

sf::Sound footsteps;
sf::SoundBuffer footstepsBuffer;


Player::Player()
{
	Load("Character1.png");
	assert(IsLoaded());
	GetSprite().setTextureRect(sf::IntRect(50, 0, 50, 50));
	footstepsBuffer.loadFromFile("footstep02.wav");
	footsteps.setBuffer(footstepsBuffer);
}

Player::~Player()
{
}

void Player::Draw(sf::RenderWindow & rw) {
	VisibleGameObject::Draw(rw);
}

float Player::GetVelocity() const
{
	return _velocity;
}

void Player::Dir(int dir)
{
	if (dir == 0) { // Down
	}
	if (dir == 1) { // Right
	}
	if (dir == 2) { // Left
	}
	if (dir == 3) { // Up
	}
}

template<typename T>
std::ostream& operator<<(std::ostream &stream, const sf::Rect<T>& rect) {
	std::cout << "[" << rect.left << ", " << rect.top << ", " << rect.width << ", " << rect.height << "]";
	return stream;
}
// Player Animation DOWN
void Player::playerAnimation_WalkDown()
{
	Dir(0);
	auto elapsedTime = mClock.getElapsedTime().asSeconds();
	const sf::IntRect walkingAnimationDown_idle(50, 0, 50, 50);
	const sf::IntRect walkingAnimationDown1(0, 0, 50, 50);
	const sf::IntRect walkingAnimationDown2(100, 0, 50, 50);
	

	if (elapsedTime < 0.2f) {
		std::cout << "frame 1\n\t" << GetSprite().getTextureRect();
		GetSprite().setTextureRect(walkingAnimationDown_idle);
		std::cout << "- " << GetSprite().getTextureRect() << "\n\n";
	}
	else if (elapsedTime < 0.3f) {
		std::cout << "frame 2\n\t" << GetSprite().getTextureRect();
		GetSprite().setTextureRect(walkingAnimationDown2);
		std::cout << "- " << GetSprite().getTextureRect() << "\n\n";
	}
	else if (elapsedTime < 0.4f) {
		GetSprite().setTextureRect(walkingAnimationDown_idle);
	}
	else if (elapsedTime < 0.5f) {
		GetSprite().setTextureRect(walkingAnimationDown1);
	}
	else if (elapsedTime > 0.5f) {
		mClock.restart();
	}
}

// Player Animation RIGHT
void Player::playerAnimation_WalkRight()
{
	Dir(1);
	auto elapsedTime = mClock.getElapsedTime().asSeconds();
	const sf::IntRect walkingAnimationRight_idle(50, 50, 50, 50);
	const sf::IntRect walkingAnimationRight1(0, 50, 50, 50);
	const sf::IntRect walkingAnimationRight2(100, 50, 50, 50);

	if (elapsedTime < 0.2f) {
		GetSprite().setTextureRect(walkingAnimationRight_idle);
	}
	else if (elapsedTime < 0.3f) {
		GetSprite().setTextureRect(walkingAnimationRight2);
	}
	else if (elapsedTime < 0.4f) {
		GetSprite().setTextureRect(walkingAnimationRight_idle);
	}
	else if (elapsedTime < 0.5f) {
		GetSprite().setTextureRect(walkingAnimationRight1);
	}
	else if (elapsedTime > 0.5f) {
		mClock.restart();
	}
}
// Player Animation LEFT
void Player::playerAnimation_WalkLeft()
{
	Dir(2);
	auto elapsedTime = mClock.getElapsedTime().asSeconds();
	const sf::IntRect walkingAnimationLeft_idle(50, 100, 50, 50);
	const sf::IntRect walkingAnimationLeft1(0, 100, 50, 50);
	const sf::IntRect walkingAnimationLeft2(100, 100, 50, 50);

	if (elapsedTime < 0.2f) {
		GetSprite().setTextureRect(walkingAnimationLeft_idle);
	}
	else if (elapsedTime < 0.3f) {
		GetSprite().setTextureRect(walkingAnimationLeft2);
	}
	else if (elapsedTime < 0.4f) {
		GetSprite().setTextureRect(walkingAnimationLeft_idle);
	}
	else if (elapsedTime < 0.5f) {
		GetSprite().setTextureRect(walkingAnimationLeft1);
	}
	else if (elapsedTime > 0.5f) {
		mClock.restart();
	}
}
// Player Animation UP
void Player::playerAnimation_WalkUp()
{
	Dir(3);
	auto elapsedTime = mClock.getElapsedTime().asSeconds();
	const sf::IntRect walkingAnimationUp_idle(50, 150, 50, 50);
	const sf::IntRect walkingAnimationUp1(0, 150, 50, 50);
	const sf::IntRect walkingAnimationUp2(100, 150, 50, 50);

	if (elapsedTime < 0.2f) {
		GetSprite().setTextureRect(walkingAnimationUp_idle);
	}
	else if (elapsedTime < 0.3f) {
		GetSprite().setTextureRect(walkingAnimationUp2);
	}
	else if (elapsedTime < 0.4f) {
		GetSprite().setTextureRect(walkingAnimationUp_idle);
	}
	else if (elapsedTime < 0.5f) {
		GetSprite().setTextureRect(walkingAnimationUp1);
	}
	else if (elapsedTime > 0.5f) {
		mClock.restart();
	}
}
void Player::Update(float elapsedTimer)
{
	float speed = 1.20f;
	sf::Time frameTime = frameClock.restart();
	// if a key was pressed set the correct animation and move correctly
	sf::Vector2f movement(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mMoving = true;
			playerAnimation_WalkLeft();
			cout << "LEFT" << endl;
			cout << GetSprite().getPosition().x << endl;
			cout << GetSprite().getPosition().y << endl;
			
			movement.x += speed;
			GetSprite().move(-movement.x, 0);

			mTime2 = mClock2.getElapsedTime();
			if (mClock2.getElapsedTime().asSeconds() >= .2f)
			{
				footsteps.play();
				mClock2.restart();
			}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mMoving = true;
			playerAnimation_WalkRight();
			cout << "RIGHT" << endl;
			cout << GetSprite().getPosition().x << endl;
			cout << GetSprite().getPosition().y << endl;
			
			movement.x += speed;
			GetSprite().move(movement.x, 0);

			mTime2 = mClock2.getElapsedTime();
			if (mClock2.getElapsedTime().asSeconds() >= .2f)
			{
				footsteps.play();
				mClock2.restart();
			}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		mMoving = true;
			playerAnimation_WalkUp();
			cout << "UP" << endl;
			cout << GetSprite().getPosition().x << endl;
			cout << GetSprite().getPosition().y << endl;
		
			movement.y += speed;
			
			GetSprite().move(0, -movement.y);
			mTime2 = mClock2.getElapsedTime();
			if (mClock2.getElapsedTime().asSeconds() >= .2f)
			{
				footsteps.play();
				mClock2.restart();
			}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		mMoving = true;
			playerAnimation_WalkDown();
			cout << "DOWN" << endl;
			cout << GetSprite().getPosition().x << endl;
			cout << GetSprite().getPosition().y << endl;
		
			movement.y += speed;
			GetSprite().move(0, movement.y);
			
			mTime2 = mClock2.getElapsedTime();
			if (mClock2.getElapsedTime().asSeconds() >= .2f)
			{
				footsteps.play();
				mClock2.restart();
			}
	}
}
Player::PlayerControlState Player::_playerControls = Walking;






