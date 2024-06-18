#pragma once
#include <SDL.h>
#include <string>


struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float initial_x, float initial_y)
	{
		x = initial_x;
		y = initial_y;
	}
};
	enum SCREENS
	{
		SCREEN_INTRO,
		SCREEN_MENNU,
		SCREEN_LEVEL1,
		SCREEN_LEVEL2,
		SCREEN_GMAEOVER,
		SCREEN_HIGHSCORES,
	};

