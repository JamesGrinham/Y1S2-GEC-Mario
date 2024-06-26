#pragma once
#include <SDL.h>
#include <iostream>
#include "commons.h"
#include "Texture2D.h"
#include <string>
#include "constants.h"
#include "LevelMap.h"

using namespace std;



class Character
{
	


protected:
	FACING m_facing_direction;
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	bool m_moving_left;
	bool m_moving_right;
	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;
	float fall_momentum;
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void AddGravity(float deltaTime);
    virtual void Jump();
	float m_collision_radius;
	int centralX_position;
	int foot_position;
	LevelMap* m_current_level_map;
	float m_movement_speed;
	bool m_alive;
	

public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~Character();

	bool IsJumping() { return m_jumping; }
	void CancelJump() { m_jump_force = 0; }
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	float GetCollisionRadius();

	void SetPosition(Vector2D new_position);

	bool GetAlive()
	{
		return m_alive;
	}
	void SetAlive(bool NewAlive)
	{
		m_alive = NewAlive;
	}

	Vector2D GetPosition();

	Rect2D GetCollisionBox() 
	{
		return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight());
	}
};
