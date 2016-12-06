#pragma once
#ifndef _CENDBKGROUND_H
#define _CENDBKGROUND_H
#include "cSprite.h"

class cEndBkGround : public cSprite
{
public:
	void render();		// Default render function
	void update();		// Update method
};
#endif