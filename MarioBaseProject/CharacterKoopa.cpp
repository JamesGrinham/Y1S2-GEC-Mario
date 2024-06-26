#include "CharacterKoopa.h"
#include "constants.h"

using namespace std;

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_injured = false;
	m_alive = true;

	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();
}
CharacterKoopa::~CharacterKoopa()
{

}
void CharacterKoopa::TakeDamage()
{
	m_injured = true;
	m_injured_time = INJURED_TIME;
	Jump();
}
void CharacterKoopa::Jump()
{
	if (!m_jumping) 
	{
	m_jump_force = INITIAL_JUMP_FORCE_SMALL;
	m_jumping = true;
	m_can_jump = false;
	}
}

void CharacterKoopa::FlipRightwayUp()
{
	if (m_facing_direction == FACING_LEFT)
	{
		m_facing_direction = FACING_RIGHT;
	}
	else
	{
		m_facing_direction = FACING_LEFT;
	}

	m_injured = false;

	Jump();
}

void CharacterKoopa::Render()
{
	// Variable to hold the left position of the sprite we want to draw
	int left = 0.0f;

	// If injured move the left position to be the left position of the second image of the sprite sheet
	if (m_injured)
	{
		left = m_single_sprite_w;
	}

	// Get the position of the sprite sheet your want to draw
	// {xPos, yPos, width of sprite, height of sprite}
	SDL_Rect portion_of_sprite = { left, 0, m_single_sprite_w, m_single_sprite_h };

	// Determine where you want it drawn
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	// Then draw it facing the correct direction
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}

}
void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	__super::Update(deltaTime, e);

	if (!m_injured)
	{
		// Enemy is not injured so move
		if (m_facing_direction == FACING_LEFT)
		{
			m_moving_left = true;
			m_moving_right = false;
		}
		else if (m_facing_direction == FACING_RIGHT)
		{
			m_moving_right = true;
			m_moving_left = false;
		}
	}
	else
	{
		// We should not be moving when injured
		m_moving_right = false;
		m_moving_left = false;

		// Count down the injured time
		m_injured_time -= deltaTime;

		if (m_allow_jump)
		{
			if (m_jump)
			{
				// Adjust position
				m_position.y -= m_jump_force * deltaTime;

				// Reduce jump force
				m_jump_force -= JUMP_FORCE_DECREMENT * 2.0f * deltaTime;

				// Is jump force 0?
				if (m_jump_force <= 0.0f)
				{
					m_jump = false;
				}
			}
			else
			{
				m_allow_jump = false;
				AddGravity(deltaTime);
				//m_allow_jump = false;
			}
		}


		if (m_injured_time <= 0.0)
		{
			FlipRightwayUp();
		}

	}

}
