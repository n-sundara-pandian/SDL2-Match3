

#include <iostream>
#include <GameStates/BaseState/GameManager.h>
#include <GameStates/CGameState.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "Utils/CRenderer.h"
#include "Utils/Common.h"
#include <Utils/CAudio.h>

void CGameManager::Init(const char* title, int width, int height, 
						 int bpp)
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0){
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return;
  }
   m_window = SDL_CreateWindow("Hello World!", 100, 100, width, height, SDL_WINDOW_SHOWN);
  if (m_window == nullptr){
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    return;
  }
  m_renderer = new CRenderer(m_window);
  TTF_Init();
  m_fontList["timer_font"] = TTF_OpenFont("data/arialbd.ttf", 60);
  m_fontList["score_font"] = TTF_OpenFont("data/arialbd.ttf", 32);
  m_fontList["button_font"] = TTF_OpenFont("data/arialbd.ttf", 24);
  m_fontList["bubble_font"] = TTF_OpenFont("data/arialbd.ttf", 16);
  CAudio::Player.Init();
  CAudio::Player.LoadWAV("Match", "data/match.ogg");
  CAudio::Player.LoadWAV("Select", "data/select.ogg");
  CAudio::Player.LoadWAV("Swap", "data/swap.wav");
  CAudio::Player.LoadWAV("Wrong", "data/click.wav");
  m_running = true;
  m_highScore = 0;
  m_lastScore = 0;
}

void CGameManager::Cleanup()
{
	// cleanup the all states
	while ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}
  if (m_renderer != nullptr)
  {
    delete m_renderer;
    m_renderer = nullptr;
  }
  CAudio::Player.Cleanup();
  SDL_DestroyWindow(m_window);
  SDL_Quit();

	
	// shutdown SDL
}

void CGameManager::ChangeState(CGameState* state) 
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init(this);
}

void CGameManager::PushState(CGameState* state)
{
	// pause current state
	if ( !states.empty() ) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init(this);
}

void CGameManager::PopState()
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// resume previous state
	if ( !states.empty() ) {
		states.back()->Resume();
	}
}


void CGameManager::HandleEvents(const SDL_Event &e)
{
	// let the state handle events
	states.back()->HandleEvents(e);
}

void CGameManager::Update(float dt) 
{
	// let the state update the game
	states.back()->Update(dt);
}

void CGameManager::Draw() 
{
  m_renderer->Clear();
	states.back()->Draw();
  m_renderer->Flip();
}

void CGameManager::SetGameSettings(int last_score)
{
  m_lastScore = last_score;
  if (last_score > m_highScore)
    m_highScore = m_lastScore;
}

void CGameManager::GetGameSettings(int &last_score, int &high_score)
{
  last_score = m_lastScore;
  high_score = m_highScore;
}
