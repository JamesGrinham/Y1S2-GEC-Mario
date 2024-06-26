#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>
#include <SDL.h>
#include "Character.h"
#include "Collisions.h"
#include "PowBlock.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"

using namespace std;


GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetLevelMap();
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1() 
{
	delete m_background_texture;
	m_background_texture = nullptr;
	delete MarioCharacter;
	MarioCharacter = nullptr; 
	delete m_pow_block;
	m_pow_block = nullptr;

	for (int i = 0; i < m_enemies.size(); i++)
	{
		delete m_enemies[i];
	}
	m_enemies.clear();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	UpdatePOWBlock();

	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		// End shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}

	MarioCharacter->Update(deltaTime, e);
	LuigiCharacter->Update(deltaTime, e);
	if (Collisions::Instance()->Circle(MarioCharacter, LuigiCharacter)) 
	{
		cout << "Circle hit!" << endl;
	}

	UpdateEnemies(deltaTime, e);
}


void GameScreenLevel1::Render()
{
	// draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	MarioCharacter->Render();
	LuigiCharacter->Render();
	m_pow_block->Render();
	//render enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}

}

void GameScreenLevel1::DoScreenshake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

bool GameScreenLevel1::SetUpLevel() 

{

	MarioCharacter = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330),m_level_map);
	LuigiCharacter = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(128, 330),m_level_map);
	CreateKoopa(Vector2D(1 * TILE_WIDTH, 1 * TILE_HEIGHT),FACING_RIGHT, KOOPA_SPEED);

	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		cout << "Failed to load test texture!" << endl;
		return false;
	}

	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;
}
void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed) 
{
	CharacterKoopa* koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", m_level_map, position, direction, speed);
	m_enemies.push_back(koopa);
}

void GameScreenLevel1::UpdatePOWBlock() 
{
	if (Collisions::Instance()->Box(m_pow_block->GetCollisionBox(), MarioCharacter->GetCollisionBox()))
	{
		cout << "Failed to load test texture!" << endl;
		//Check if the POW block is available
		if (m_pow_block->IsAvailable())
		{
			//Check and manage Mario's jump state
			if (MarioCharacter->IsJumping())
			{
				m_pow_block->TakeHit();
				MarioCharacter->CancelJump();
				DoScreenshake();


			}
		}
	}
}
void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//check if the enemy is on the bottom row of tiles
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				//is the enemy off screen to the left / right?
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[
					i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f))
					m_enemies[i]->SetAlive(false);
			}
			//now do the update

			m_enemies[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->
				GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], MarioCharacter))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{

					}
				}
				if (Collisions::Instance()->Circle(m_enemies[i], LuigiCharacter))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{

					}
				}

				//if the enemy is no longer alive then schedule it for deletion
				if (!m_enemies[i]->GetAlive())
				{
					enemyIndexToDelete = i;
				}
			}

			//remove dead enemies -1 each update

			if (enemyIndexToDelete != -1)
			{
				m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
			}
		}
	}
}
	void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
										{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 }, // Remember to change the two middle 0s to 1 when we are working with POW block.
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	// Clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	// Set the new one
	m_level_map = new LevelMap(map);


}

