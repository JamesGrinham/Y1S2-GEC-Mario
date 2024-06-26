#pragma once
#include <SDL.h>
#include "Character.h"
#include "constants.h"

class CharacterKoopa : public Character 
{
private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;
	void FlipRightwayUp();
	float m_allow_jump;
	float m_jump;

public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~CharacterKoopa();
	void TakeDamage();
	void Jump();
	void Render() override;
	bool GetInjured()
	{
		return m_injured;
	}
	void Update(float deltaTime, SDL_Event e) override;
};

