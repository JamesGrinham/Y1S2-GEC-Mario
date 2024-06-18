#pragma once
#include "commons.h"
#include "GameScreen.h"
#include "SDL.h"
#include <string>
#include "commons.h"

class Texture2D;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* m_background_texture;
	bool SetUpLevel();

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Update(float deltaTime, SDL_Event e);

	void Render() override;

};




