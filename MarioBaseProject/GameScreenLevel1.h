#pragma once
#include "commons.h"
#include "GameScreen.h"
#include "SDL.h"
#include <string>
#include "commons.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include <vector>
#include "CharacterKoopa.h"

class Texture2D;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* m_background_texture;
	bool SetUpLevel();
	void SetLevelMap();
	CharacterMario* MarioCharacter;
	CharacterLuigi* LuigiCharacter;
	CharacterKoopa* KoopaCharacter;
	LevelMap* m_level_map;
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	PowBlock* m_pow_block;
	void DoScreenshake();

	void UpdatePOWBlock();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	vector<CharacterKoopa*> m_enemies;


public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Update(float deltaTime, SDL_Event e);

	void Render() override;

};




