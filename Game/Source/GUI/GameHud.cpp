#include "GameHud.h"
#include <GUI/Timer.h>
#include "SDL_log.h"
#include "../../../../../King/Match3/Lib/SDL2-2.0.3/include/SDL_rect.h"
#include "Utils/Vector.h"
#include "Utils/CTextRenderer.h"
#include "SDL_surface.h"
#include "gamestates/basestate/GameManager.h"

GameHUD::GameHUD(CGameManager *game)
  : m_game(game)
  , m_targetTime(60)
  , m_score(0)
  , m_pause(false)
  , m_isGameOver(false)
{
  m_timer = new CTimer();
  m_timer->Init(this, 60, &GameHUD::GameOver);
  m_timertext = new CTextRenderer(m_game->GetRenderer());
  m_timertext->SetColor(255, 0, 0);
}
void GameHUD::Update(float dt)
{
  m_timer->Tick(dt);
}
void GameHUD::Draw()
{
  m_timertext->DrawText(m_game->GetFont("timer_font"), std::to_string(m_timer->GetRemainingTime()), Vector2i(50, 50));
}

void GameHUD::GameOver()
{
  m_isGameOver = true;
  SDL_Log(" game Over ");
}

void GameHUD::Pause() { m_timer->Pause(); }
void GameHUD::Resume() { m_timer->Resume(); }
bool GameHUD::IsGameOver() { return m_isGameOver; }
