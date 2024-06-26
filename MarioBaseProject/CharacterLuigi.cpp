#include "CharacterLuigi.h"

using namespace std;

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
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

    CharacterLuigi::~CharacterLuigi()
    {

    }

    void CharacterLuigi::Update(float deltaTime, SDL_Event e)
    {
        __super::Update(deltaTime, e);
        switch (e.type)
        {
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym)
            {
            case SDLK_a:
                m_moving_left = true;
                break;
            case SDLK_d:
                m_moving_right = true;
                break;
            case SDLK_w:
                if (m_can_jump)
                {
                    Jump();
                }
            }
            break;

        case SDL_KEYUP:
            switch (e.key.keysym.sym)
            {
            case SDLK_a:
                m_moving_left = false;
                break;
            case SDLK_d:
                m_moving_right = false;
                break;
            }
            break;
        }
}

