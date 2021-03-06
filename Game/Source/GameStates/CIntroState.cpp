


#include <iostream>
#include <GameStates/BaseState/GameManager.h>
#include <GameStates/CGameState.h>
#include <GameStates/CIntroState.h>
#include <GameStates/CPlayState.h>
#include "SDL_image.h"
#include "Utils/CRenderer.h"

CIntroState CIntroState::m_IntroState;

void CIntroState::Init(CGameManager* game)
{
  m_game = game;
  SDL_assert(m_game != nullptr);
	m_timeout = 0.5f;
  m_elapsed_time = 0.0f;
  m_active = true;
  m_splash = m_game->GetRenderer()->LoadImage("data/BackGround.png");
  SDL_assert(m_splash != nullptr);
}

void CIntroState::Cleanup()
{

}

void CIntroState::Pause()
{
}

void CIntroState::Resume()
{
}

void CIntroState::HandleEvents(const SDL_Event &e)
{

}

void CIntroState::Update( float dt) 
{
  if (m_active)
    m_elapsed_time += dt;
  if (m_elapsed_time > m_timeout && m_active)
  {
    m_active = false;
    m_game->ChangeState(CPlayState::Instance());
  }
}

void CIntroState::Draw() 
{
  m_game->GetRenderer()->Render( m_splash);
}
