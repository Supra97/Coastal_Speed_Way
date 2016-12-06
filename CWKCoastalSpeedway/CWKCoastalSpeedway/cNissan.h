/*
=================
cNIssan.h
- Header file for class definition - SPECIFICATION
- Header file for the Rocket class which is a child of cSprite class
=================
*/
#ifndef _CNISSAN_H
#define _CNISSAN_H
#include "cSprite.h"

class cNissan : public cSprite
{
private:
	SDL_Point nissanVelocity;

public:
	cNissan();
	void update(double deltaTime);		// Rocket update method
	void setNissanVelocity(SDL_Point nissanVel);   // Sets the velocity for the rocket
	SDL_Point getNissanVelocity();				 // Gets the rocket velocity
};
#endif