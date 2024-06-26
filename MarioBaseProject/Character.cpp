#include "Character.h"
#include <SDL.h>
#include <iostream>
#include "commons.h"
#include "Texture2D.h"
#include <string>
#include "constants.h"
#include "LevelMap.h"

using namespace std;


Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map)
{
    m_current_level_map = map;
    m_renderer = renderer;
	m_position = start_position;
    m_moving_left = false;
    m_moving_right = false;
	m_texture = new Texture2D(m_renderer);
    m_facing_direction == FACING_RIGHT;
    m_collision_radius = 15.0f;

	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background texture!" << std::endl;
	}

}

Character::~Character()
{
	m_renderer = nullptr;
}

void Character::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE);
    if (m_facing_direction == FACING_RIGHT)
    {
        m_texture->Render(m_position, SDL_FLIP_NONE);
    }
    else
    {
        m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
    }
}

void Character::MoveLeft(float deltaTime)
{
    m_facing_direction = FACING_LEFT;
    m_position.x -= deltaTime * MOVEMENTSPEED;
}

void Character::MoveRight(float deltaTime)
{
    m_facing_direction = FACING_RIGHT;
    m_position.x += deltaTime * MOVEMENTSPEED;
}

void Character::Update(float deltaTime, SDL_Event e)
{
    // Collision position variables 
     centralX_position = (int)(m_position.x + (m_texture->GetWidth() * 0.5f)) / TILE_WIDTH;
     foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;

    AddGravity(deltaTime);

    //deal with jumping first
    if (m_jumping)
    {
        //adjust position
        m_position.y -= m_jump_force * deltaTime;

        //reduce jump force
        m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

        //is jump force 0?
        if (m_jump_force <= 0.0f)
            m_jumping = false;
    }

    if (m_moving_left)
    {
        MoveLeft(deltaTime);
    }
    else if (m_moving_right)
    {
        MoveRight(deltaTime);
    }
}

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;

}

Vector2D Character::GetPosition()
{
	return m_position;
}


void Character::Jump()
{
    if(!m_jumping)
    {
	//JUMP
    m_jump_force = INITIAL_JUMP_FORCE;
	m_jumping = true;
	m_can_jump = false;
    }
}

void Character::AddGravity(float deltaTime)
{
    if (m_current_level_map == nullptr)
    {
        return;
    }
    if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
    {
        m_can_jump = false;
        m_position.y += GRAVITY * deltaTime;
    }
    else
    {
        //collided with ground so we can jump again
        m_can_jump = true;
    }
}
float Character::GetCollisionRadius()
{
    return m_collision_radius;
}