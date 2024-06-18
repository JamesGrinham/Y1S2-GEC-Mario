#pragma once
#include <SDL.h>
#include <iostream>
#include "commons.h"
#include "Texture2D.h"
#include <string>
#include "constants.h"

using namespace std;



class Characters
{
protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;

public: 
	Characters(SDL_Renderer* renderer, string imagePath, Vector2D start_position);
	~Characters();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D new_position);

	bool m_moving_left, m_moving_right, m_can_jump; 
	bool m_jumping, m_can_jump;
	float m_jump_force;


	Vector2D GetPosition();

	void Jump();

};

