#include "Characters.h"
#include <SDL.h>
#include <iostream>
#include "commons.h"
#include "Texture2D.h"
#include <string>
#include "constants.h"

using namespace std;


Characters::Characters(SDL_Renderer* renderer, string imagePath, Vector2D start_position)
{
	m_renderer = renderer;
	m_position = start_position;
	m_texture->LoadFromFile(imagePath);
}

Characters::~Characters()
{
	m_renderer = nullptr;
}

void Characters::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE);
}


void Characters::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = true;
			break;
		case SDLK_RIGHT:
			m_moving_right = true;
			break;
		case SDLK_UP:
			if (m_can_jump)
			{
				Jump();
			}
		}
		break;
	}
}

void Characters::SetPosition(Vector2D new_position)
{

}

void Characters::Jump()
{
	//JUMP
	//m_jump_force = INITIAL_JUMP_FORCE;
	m_jumping = true;
	m_can_jump = false;

}