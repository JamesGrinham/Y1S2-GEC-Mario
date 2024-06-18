#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "GameScreenManager.h"
#include "Texture2D.h"
#include "commons.h"
#include "constants.h"
#include <iostream>

using namespace std;

GameScreenManager* game_screen_manager;
Uint32 g_old_time;
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
Texture2D* g_texture = nullptr;
SDL_Texture* p_texture = nullptr;

bool InitSDL();
void CloseSDL();
bool Update();
void Render();
SDL_Texture* LoadTextureFromFile(string path);
void FreeTexture();


int main(int argc, char* args[])
{
	if (InitSDL()) 
	{


		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
		//set the time
		g_old_time = SDL_GetTicks();

		bool quit = false;

		while (!quit)
		{
			Render();

			quit = Update();

		}
	}
	CloseSDL();
	
	return 0;
}


bool InitSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		g_window = SDL_CreateWindow("Games Engine Creation", 
			SDL_WINDOWPOS_UNDEFINED,  
			SDL_WINDOWPOS_UNDEFINED, 
			SCREEN_WIDTH, 
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		if (g_window == nullptr)
		{
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

		if (g_renderer != nullptr)
		{
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL image could not initialise. Error: " << IMG_GetError();
				return false;
			}
			/*
			g_texture = new Texture2D(g_renderer);
			if (!g_texture->LoadFromFile("Images/test.bmp"))
			{
				return false;
			}
			*/
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}

	}
	return true;
}


void CloseSDL()
{
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	IMG_Quit();
	SDL_Quit();

	/*
	delete g_texture;
	g_texture = nullptr;
	*/

	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

	//destroy the game screen manmager
	delete game_screen_manager;
	game_screen_manager = nullptr;

}

bool Update()
{
	Uint32 new_time = SDL_GetTicks();
	SDL_Event e;

	SDL_PollEvent(&e);

	switch (e.type)
	{
	case SDL_QUIT:
		return true;
		break;
	}

		game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
		g_old_time = new_time;
	
	return false;
}

void Render()
{
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);
	
	game_screen_manager->Render();

	SDL_RenderPresent(g_renderer);
}

//SDL_Texture* LoadTextureFromFile(string path)
//{
//	FreeTexture();
//	SDL_Texture* p_texture = nullptr;
//
//
//
//	SDL_Surface* p_surface = IMG_Load(path.c_str());
//	if (p_surface != nullptr)
//	{
//		p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
//		if (p_texture == nullptr)
//		{
//			cout << "Unable to create texture from surface. Error: " << SDL_GetError();
//		}
//		SDL_FreeSurface(p_surface);
//	}
//	else
//	{
//		cout << "Unable to create texture from surface. Error: " << IMG_GetError();
//	}
//	return p_texture;
//}

//void FreeTexture()
//{
//	if (g_texture != nullptr)
//	{
//		SDL_DestroyTexture(g_texture);
//		g_texture = nullptr;
//	}
//}