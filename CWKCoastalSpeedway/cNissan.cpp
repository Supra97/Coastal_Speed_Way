/*
=================
cRocket.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cNissan.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cNissan::cNissan() : cSprite()
{
	this->nissanVelocity = { 0.0f, 0.0f };
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cNissan::update(double deltaTime)
{

	FPoint direction = { 0.0f, 0.0f };
	
	direction.X *= this->getSpriteTranslation().x;
	direction.Y *= this->getSpriteTranslation().y;

	this->nissanVelocity.x = this->nissanVelocity.x + direction.X;
	this->nissanVelocity.y = this->nissanVelocity.y + direction.Y;

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->nissanVelocity.x * deltaTime;
	currentSpritePos.y += this->nissanVelocity.y * deltaTime;

	this->nissanVelocity.x *= 2;
	this->nissanVelocity.y *= 2;
	
	this->setSpritePos({ currentSpritePos.x , currentSpritePos.y  });
	this->setBoundingRect(this->getSpritePos());
}
/*
=================================================================
Sets the velocity for the rocket
=================================================================
*/
void cNissan::setNissanVelocity(SDL_Point nissanVel)
{
	nissanVelocity = nissanVel;
}
/*
=================================================================
Gets the rocket velocity
=================================================================
*/
SDL_Point cNissan::getNissanVelocity()
{
	return nissanVelocity;
}


/*
=================================================================
Update the sprite position
=================================================================
*/


