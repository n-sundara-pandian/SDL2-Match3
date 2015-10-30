

#include <iostream>


#include <GameStates/CGameState.h>
#include <GameStates/BaseState/GameManager.h>
#include <GameStates/CPlayState.h>
#include <GameStates/CMenuState.h>
#include "SDL_image.h"
#include "Utils/Renderer.h"

CPlayState CPlayState::m_PlayState;
using namespace std;
void CPlayState::Init(CGameManager* game)
{
  SDL_assert(game != nullptr);
  m_game = game;
  m_bg = m_game->GetRenderer()->loadImage("data/BackGround.jpg");
  SDL_assert(m_bg != nullptr);

}

void CPlayState::Cleanup()
{
  
}

void CPlayState::Pause()
{
}

void CPlayState::Resume()
{
}

void CPlayState::HandleEvents(const SDL_Event &e)
{
  //if (e.type == SDL_KEYDOWN)
  switch (e.type)
  {
  case SDL_KEYDOWN:
    switch (e.key.keysym.sym)
    {
      case SDLK_ESCAPE:
      {
        m_game->Quit();
        break;
      }
      case SDLK_m:
      {
        m_game->PushState(CMenuState::Instance());
        break;
      }
    }
    break;
  case SDL_MOUSEBUTTONDOWN:
    if (e.button.button == SDL_BUTTON_LEFT)
    {
      //Get the mouse offsets
      cout <<  e.button.x + " " +  e.button.y;
    }
  default:
    break;
  }
}

void CPlayState::Update(float dt)
{

}

void CPlayState::Draw()
{
  SDL_assert(m_bg != nullptr);
  m_game->GetRenderer()->renderTexture(m_bg);

}

