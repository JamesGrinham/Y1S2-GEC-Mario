#include "GameScreen.h"
#include <SDL.h>
#include "Texture2D.h"
#include "commons.h"
#include "constants.h"
#include <iostream>

GameScreen::GameScreen(SDL_Renderer* renderer) 
{
	m_renderer = renderer;
}
GameScreen::~GameScreen() 
{
	m_renderer = nullptr;
}

void GameScreen::Render()
{

}
void GameScreen::Update(float deltaTime, SDL_Event e)
{

}
