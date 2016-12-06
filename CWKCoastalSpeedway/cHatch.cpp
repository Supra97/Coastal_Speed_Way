/*
=================
cHatch.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cHatch.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cHatch::cHatch() : cSprite()
{
	this->hatchVelocity = { 0.0, 0.0 };
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cHatch::update(double deltaTime)
{

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->getSpriteTranslation().x * deltaTime +5;
	currentSpritePos.y += this->getSpriteTranslation().y * deltaTime;

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y });
	cout << "Hatch position - x: " << this->getSpritePos().x << " y: " << this->getSpritePos().y << " deltaTime: " << deltaTime << endl;
	this->setBoundingRect(this->getSpritePos());
}
/*
void cHatch::sethatchVelocity(SDL_Point hatchvel)
{
	hatchVelocity = hatchvel;
}
SDL_Point cHatch::gethatchVelocity()
{
	return hatchVelocity;
	if (this->getSpritePos().y <= 768)
	{
		this->setSpritePos({ this->getSpritePos().x, 0 });
	 }

}*/
/*
=================================================================
  Sets the velocity for the Hatch
=================================================================
*/
void cHatch::sethatchVelocity(SDL_Point hatchVel)
{
	hatchVelocity = hatchVel;
}
/*
=================================================================
  Gets the Hatch velocity
=================================================================
*/
SDL_Point cHatch::gethatchVelocity()
{
	return hatchVelocity;
}
