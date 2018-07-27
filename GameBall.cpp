#include "stdafx.h"
#include "GameBall.h"
#include "Game.h"
#include "ServiceLocator.h"

GameBall::GameBall() :
	_velocity(230.0f),
	_elapsedTimeSinceStart(0.0f),
	_runYet(false)
{
	Load("Snow.png");
	assert(IsLoaded());

	GetSprite().setOrigin(15, 15);
	float random_integer = std::rand() % 360 + 1; //Gives random number between 1 and 360.
	_angle = random_integer;
	//_angle = (float)(sf::Randomizer::Random(0,360);
}


GameBall::~GameBall()
{
}


void GameBall::Update(float elapsedTime) //Parameter is the time since last frame in seconds. VERY small number.
{
	if (_runYet == false)
		_runYet = true;
	else
	{
		_elapsedTimeSinceStart += elapsedTime;

		// Delay game from starting until 3 seconds have passed
		if (_elapsedTimeSinceStart < 3.0f)
			return;

		float moveAmount = _velocity * elapsedTime;


		float moveByX = LinearVelocityX(_angle) * moveAmount;
		float moveByY = LinearVelocityY(_angle) * moveAmount;


		//collide with the left side of the screen
		if (GetPosition().x + moveByX <= 0 + GetWidth() / 2 || GetPosition().x + GetHeight() / 2 + moveByX >= Game::WINDOW_WIDTH)
		{
			//Ricochet!
			_angle = 360.0f - _angle;
			if (_angle > 260.0f && _angle < 280.0f) _angle += 20.0f;
			if (_angle > 80.0f && _angle < 100.0f) _angle += 20.0f;
			moveByX = -moveByX;
		}



		PlayerPaddle* player1 = dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get("Paddle1"));
		if (player1 != NULL)
		{
			sf::Rect<float> p1BB = player1->GetBoundingRect();

			if (p1BB.intersects(GetBoundingRect()))       //(GetPosition().x + moveByX + (GetSprite().GetSize().x /2),GetPosition().y + (GetSprite().GetSize().y /2) + moveByY))
			{
				_angle = 360.0f - (_angle - 180.0f);
				if (_angle > 360.0f) _angle -= 360.0f;



				moveByY = -moveByY;

				// Make sure ball isn't inside paddle
				if (GetBoundingRect().width > player1->GetBoundingRect().top)
				{
					SetPosition(GetPosition().x, player1->GetBoundingRect().top - GetWidth() / 2 - 1);
				}

				// Now add "English" based on the players velocity.  
				float playerVelocity = player1->GetVelocity();

				if (playerVelocity < 0)
				{
					// moving left
					_angle -= 20.0f;
					if (_angle < 0) _angle = 360.0f - _angle;
				}
				else if (playerVelocity > 0)
				{
					_angle += 20.0f;
					if (_angle > 360.0f) _angle = _angle - 360.0f;
				}

				ServiceLocator::GetAudio()->PlaySound("audio/kaboom.wav");
				_velocity += 5.0f;
			}

			if (GetPosition().y - GetHeight() / 2 <= 0)
			{
				_angle = 180 - _angle;
				moveByY = -moveByY;
			}


			//if(GetPosition().y - GetSprite().GetSize().y/2 - moveByY <= 0 || GetPosition().y + GetSprite().GetSize().y/2 + moveByY >= Game::SCREEN_HEIGHT)
			if (GetPosition().y + GetHeight() / 2 + moveByY >= Game::WINDOW_HEIGHT)
			{
				// move to middle of the screen for now and randomize angle
				GetSprite().setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
				_angle = (rand() % 360) + 1;
				_velocity = 230.0f;
				_elapsedTimeSinceStart = 0.0f;
			}

			GetSprite().move(moveByX, moveByY);
		}
	}
}


float GameBall::LinearVelocityX(float angle)
{
	angle -= 90;
	if (angle < 0) angle = 360 + angle;
	return (float)std::cos(angle * (3.1415926 / 180.0f));
}

float GameBall::LinearVelocityY(float angle)
{
	angle -= 90;
	if (angle < 0) angle = 360 + angle;
	return (float)std::sin(angle * (3.1415926 / 180.0f));
}
