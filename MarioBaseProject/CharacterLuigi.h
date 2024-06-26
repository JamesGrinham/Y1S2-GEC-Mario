#pragma once
#include "Character.h"
#include <SDL.h>

class CharacterLuigi : public Character
{

public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterLuigi();

	void Update(float deltaTime, SDL_Event e);
};



