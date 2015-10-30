

#include <iostream>
#include <GameStates/BaseState/GameManager.h>
#include <GameStates/CGameState.h>
#include "SDL.h"
#include "Utils/Renderer.h"

void CGameManager::Init(const char* title, int width, int height, 
						 int bpp)
{

  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return;
  }
   m_window = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
  if (m_window == nullptr){
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    return;
  }
  m_renderer = new Renderer(m_window);
  //m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  //if (m_renderer == nullptr){
  //  std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
  //  return;
  //}
  m_running = true;
  cout << "CGameEngine Init\n";
}

void CGameManager::Cleanup()
{
	// cleanup the all states
	while ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

  SDL_DestroyWindow(m_window);
  SDL_Quit();

	cout << "CGameEngine Cleanup\n";

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
  m_renderer->clear();
	// let the state draw the screen
	states.back()->Draw();
  m_renderer->flip();
}
