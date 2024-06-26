#include "CharacterMario.h"

using namespace std;

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{
    m_renderer = renderer;
    m_position = start_position;
    m_moving_left = false;
    m_moving_right = false;
    m_texture = new Texture2D(m_renderer);
    m_facing_direction == FACING_RIGHT;
    m_current_level_map = map;

    if (!m_texture->LoadFromFile(imagePath))
    {
        std::cout << "Failed to load background texture!" << std::endl;
    }
}

CharacterMario::~CharacterMario()
{
	
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
    __super::Update(deltaTime, e);
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

        case SDL_KEYUP:
            switch (e.key.keysym.sym)
            {
            case SDLK_LEFT:
                m_moving_left = false;
                break;
            case SDLK_RIGHT:
                m_moving_right = false;
                break;
            }
            break;
    }
}


