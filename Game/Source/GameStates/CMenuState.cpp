


#include <iostream>
#include <GameStates/BaseState/GameManager.h>
#include <GameStates/CGameState.h>
#include <GameStates/CMenuState.h>
#include "Utils/Renderer.h"

CMenuState CMenuState::m_MenuState;

void CMenuState::Init(CGameManager* game)
{
  SDL_assert(game != nullptr);
  m_game = game;

}

void CMenuState::Cleanup()
{
}

void CMenuState::Pause()
{
}

void CMenuState::Resume()
{
}

void CMenuState::HandleEvents(const SDL_Event &e)
{
  if (e.type == SDL_KEYDOWN)
  {
    switch (e.key.keysym.sym)
    {
      case SDLK_q:
      {
        m_game->Quit();
        break;
      }
      case SDLK_SPACE:
      {
        m_game->PopState();
        break;
      }
    }
  }
}

void CMenuState::Update( float dt) 
{

}

void CMenuState::Draw() 
{
}
