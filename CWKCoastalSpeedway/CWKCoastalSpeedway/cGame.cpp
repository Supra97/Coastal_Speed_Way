/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
static cFontMgr* theFontMgr = cFontMgr::getInstance();
static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();


/*
=================================================================================
Constructor
=================================================================================
*/
cGame::cGame()
{

}
/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cGame* cGame::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cGame();
	}
	return cGame::pInstance;
}


void cGame::initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	// Get width and height of render context
	SDL_GetRendererOutputSize(theRenderer, &renderWidth, &renderHeight);
	this->m_lastTime = high_resolution_clock::now();
	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);
	
	theTextureMgr->setRenderer(theRenderer);
	theFontMgr->initFontLib();
	theSoundMgr->initMixer();

	// Store the textures
	textureName = { "Hatchback", "Hatchback2", "Hatchback3", "Hatchback4","theNissan","theBackground"," menuBkgd", "endBkgdd"};
	texturesToUse = { "Images/Hatchback.png", "Images/Hatchback2.png", "Images/Hatchback3.png", "Images/Hatchback4.png", "Images/Nissan.png", "Images/MainLevel.png", "Images/CoastalSpeedwayMenu.png","Images/GameOver.png" };
	for (int tCount = 0; tCount < textureName.size(); tCount++)
	{	
		theTextureMgr->addTexture(textureName[tCount], texturesToUse[tCount]);
	}
	// Create textures for Game Dialogue (text)
	fontList = { "digital", "spaceAge" };
	fontsToUse = { "Fonts/digital-7.ttf", "Fonts/space age.ttf" };
	for (int fonts = 0; fonts < fontList.size(); fonts++)
	{
		theFontMgr->addFont(fontList[fonts], fontsToUse[fonts], 36);
	}
	gameTextList = { "Score"};
	
	theTextureMgr->addTexture("ScoreTxt", theFontMgr->getFont(fontList[1])->createTextTexture(theRenderer, gameTextList[0], SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));

	// Load game sounds
	soundList = { "theme", "car" /*"explosion"*/ };
	soundTypes = { MUSIC, SFX };
	soundsToUse = { "Audio/223475__zagi2_jolly-game-groove.wav", "Audio/34176__charliefarley_engine1.wav" /*"Audio/explosion2.wav"*/ };
	for (int sounds = 0; sounds < soundList.size(); sounds++)
	{
		theSoundMgr->add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]);
	}

	theSoundMgr->getSnd(soundList[0])->play(-1);
	// initialises the menu background
	menuBkgd.setSpritePos({ 0, 0 });
	menuBkgd.setTexture(theTextureMgr->getTexture(textureName[6]));
	menuBkgd.setSpriteDimensions(theTextureMgr->getTexture(textureName[6])->getTWidth(), theTextureMgr->getTexture(textureName[6])->getTHeight());
	// initialises level background
	spriteBkgd.setSpritePos({ 0, 0 });
	spriteBkgd.setTexture(theTextureMgr->getTexture(textureName[5]));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture(textureName[5])->getTWidth(), theTextureMgr->getTexture(textureName[5])->getTHeight());
	//intialises the end background
	endBkgd.setSpritePos({ 0, 0 });
	endBkgd.setTexture(theTextureMgr->getTexture(textureName[7]));
	endBkgd.setSpriteDimensions(theTextureMgr->getTexture(textureName[7])->getTWidth(), theTextureMgr->getTexture(textureName[7])->getTHeight()); // initialises end background 
	 																																		 
	// initialises nissan sprite and positon 																													 
	theNissan.setSpritePos({ 500, 350 });
	theNissan.setTexture(theTextureMgr->getTexture(textureName[4]));
	theNissan.setSpriteDimensions(theTextureMgr->getTexture(textureName[4])->getTWidth(), theTextureMgr->getTexture(textureName[4])->getTHeight());
	theNissan.setNissanVelocity({ 0, 0 });

	// Create vector array of textures
	theGameState = MENU;
	for (int hatch = 0; hatch < 4; hatch++)
	{
		theHatchs.push_back(new cHatch);
		int xPostion = 100 * (rand() % 5 + 1) + 500;
		int yPostion = 100 * (rand() % 5 + 1);
		if (yPostion > 0) { xPostion = 512;  }
		theHatchs[hatch]->setSpritePos({ 100 * (rand() % 5 + 1), 50 * (rand() % 5 + 1) });
		theHatchs[hatch]->setSpriteTranslation({ (rand() % 8 + 1), (rand() % 8 + 1) });
		int randHatch = rand() % 4;
		theHatchs[hatch]->setTexture(theTextureMgr->getTexture(textureName[randHatch]));
		theHatchs[hatch]->setSpriteDimensions(theTextureMgr->getTexture(textureName[randHatch])->getTWidth(), theTextureMgr->getTexture(textureName[randHatch])->getTHeight());
		theHatchs[hatch]->sethatchVelocity({ 3.0f, 3.0f });
		theHatchs[hatch]->setActive(true);
	}

}

void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	bool loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		double elapsedTime = this->getElapsedSeconds();

		loop = this->getInput(loop);
		this->update(elapsedTime);
		this->render(theSDLWND, theRenderer);
	}
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	
			SDL_RenderPresent(theRenderer);
		if (theGameState == MENU)
		{
		menuBkgd.render(theRenderer, NULL, NULL, menuBkgd.getSpriteScale());
		
		}
		
		if (theGameState == PLAYING)
		
		{
			
			SDL_RenderPresent(theRenderer);
			spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
			// Render each hatchbacks in the vector array
			for (int draw = 0; draw < theHatchs.size(); draw++)
			{
				theHatchs[draw]->render(theRenderer, &theHatchs[draw]->getSpriteDimensions(), &theHatchs[draw]->getSpritePos(), theHatchs[draw]->getSpriteRotAngle(), &theHatchs[draw]->getSpriteCentre(), theHatchs[draw]->getSpriteScale());
			}


			// Render the Title
//			theTextureMgr->addTexture("Score", theFontMgr->getFont("spaceAge")->createTextTexture(theRenderer, "Score: " + to_string(score).c_str, SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));

			cTexture* tempTextTexture = theTextureMgr->getTexture("ScoreTxt");
			SDL_Rect pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
			FPoint scale = { 1, 1 };
			tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
			// render the rocket
			theNissan.render(theRenderer, &theNissan.getSpriteDimensions(), &theNissan.getSpritePos(), theNissan.getSpriteRotAngle(), &theNissan.getSpriteCentre(), theNissan.getSpriteScale());
		}
		if (theGameState == END)
		{
			
			endBkgd.render(theRenderer, NULL, NULL, endBkgd.getSpriteScale());// renders background
			//theTextureMgr->addTexture("Score", theFontMgr->getFont("spaceAge")->createTextTexture(theRenderer, "Score: " + to_string(score).c_str, SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));

			cTexture* tempTextTexture = theTextureMgr->getTexture("Score");
			SDL_Rect pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
			FPoint scale = { 1, 1 };
			tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);// renders score in position 

			theSoundMgr->getSnd("theme")->play(1); // plays music. 
			
		}
	SDL_RenderPresent(theRenderer);

		}




void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre)
{

	SDL_RenderPresent(theRenderer);
}

void cGame::update()
{

}

void cGame::update(double deltaTime)
{
	if (theGameState == PLAYING)
	{
		// Update the visibility and position of each asteriod
		vector<cHatch*>::iterator hatchIterator = theHatchs.begin();
		while (hatchIterator != theHatchs.end())
		{
			if ((*hatchIterator)->isActive() == false)
			{
				hatchIterator = theHatchs.erase(hatchIterator);
			}
			else
			{
				(*hatchIterator)->update(deltaTime);
				++hatchIterator;
			}
		}

		/*
		==============================================================
		| Check for collisions
		==============================================================
		*/
		for (vector<cHatch*>::iterator hatchIterartor = theHatchs.begin(); hatchIterartor != theHatchs.end(); ++hatchIterartor)
		{
			if (theNissan.collidedWith(&(theNissan.getBoundingRect()), &(*hatchIterator)->getBoundingRect()))
			{
				// if a collision set the hatch and  to false
				(*hatchIterator)->setActive(false);
				(&theNissan)->setActive(false);
				theSoundMgr->getSnd("explosion")->play(0);
			}



			// Update the Rockets position
			theNissan.update(deltaTime);
		}
	}
}

bool cGame::getInput(bool theLoop)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			theLoop = false;
		}

		switch (event.type)
		{

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
			{
				theLoop = false;
				break;
			}
			case SDLK_RETURN:
			{
				
					(theGameState == PLAYING);
					theSoundMgr->getSnd("theme")->play(1);


				}
			}
			break;
			{

				if (theGameState == PLAYING)
				{
			case SDLK_DOWN:
			{
				if (theNissan.getSpritePos().x < (renderWidth - theNissan.getSpritePos().w))
				{
					theNissan.setSpriteTranslation({ 0, -50 });
				}
			}
			break;

			case SDLK_UP:
			{
				if (theNissan.getSpritePos().x > 0)
				{
					theNissan.setSpriteTranslation({ 0, +50 });
				}
			}
			break;
			case SDLK_RIGHT:
			{
				if (theNissan.getSpritePos().x > 0)
				{
					theNissan.setSpriteTranslation({ +50 });
				}
			}
			break;

			case SDLK_LEFT:
			{
				if (theNissan.getSpritePos().x > 0)
				{
					theNissan.setSpriteTranslation({ +50, 0 });
				}
			}
			break;
			case SDLK_SPACE:
			{
				if (theNissan.getSpritePos().y < (renderWidth - theNissan.getSpritePos().w))
				{
					theNissan.setSpriteTranslation({ +60 });
				}

			}

			default:
				break;
				}

			}
			}
		}
	}
			return theLoop;
}

double cGame::getElapsedSeconds()
{
	this->m_CurrentTime = high_resolution_clock::now();
	this->deltaTime = (this->m_CurrentTime - this->m_lastTime);
	this->m_lastTime = this->m_CurrentTime;
	return deltaTime.count();
}

void cGame::cleanUp(SDL_Window* theSDLWND)
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(theSDLWND);

	// Destroy the window
	SDL_DestroyWindow(theSDLWND);

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}

