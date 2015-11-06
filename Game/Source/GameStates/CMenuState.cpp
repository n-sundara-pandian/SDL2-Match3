


#include <iostream>
#include <GameStates/BaseState/GameManager.h>
#include <GameStates/CGameState.h>
#include <GameStates/CMenuState.h>
#include <GameStates/CPlayState.h>
#include <Utils/CRenderer.h>
#include <Utils/Vector.h>
#include <Utils/CTextRenderer.h>
#include <Match3/CItem.h>
#include <Utils/Common.h>

CMenuState CMenuState::m_MenuState;

void CMenuState::Init(CGameManager* game)
{
  SDL_assert(game != nullptr);
  m_game = game;
  m_gameOverText = std::make_unique<CTextRenderer>(m_game->GetRenderer());
  m_game->GetGameSettings(m_lastScore, m_highScore);
  m_msg = " You Scored " + std::to_string(m_lastScore) ;
  m_msg1 =  "Your High score is " + std::to_string(m_highScore);
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
      case SDLK_ESCAPE:
      {
        m_game->Quit();
        break;
      }
      case SDLK_SPACE:
      {
        m_game->ChangeState(CPlayState::Instance());
        break;
      }
    }
  }
  else if (e.type == SDL_MOUSEBUTTONDOWN)
  {
    if (e.button.button == SDL_BUTTON_LEFT)
    {
      m_game->ChangeState(CPlayState::Instance());

    }
  }
}

void CMenuState::Update( float dt) 
{

}

void CMenuState::Draw() 
{
  m_gameOverText->DrawText(m_game->GetFont("button_font"), m_msg, Vector2i(50, 150));
  m_gameOverText->SetColor(Utils::GetColor(CItem::Color::Green));
  m_gameOverText->DrawText(m_game->GetFont("button_font"), m_msg1, Vector2i(50, 200));
  m_gameOverText->SetColor(Utils::GetColor(CItem::Color::Green));
  m_gameOverText->DrawText(m_game->GetFont("button_font"), "Click to Continue ... ESC to quit", Vector2i(50, 250));
  m_gameOverText->SetColor(Utils::GetColor(CItem::Color::Red));
}
