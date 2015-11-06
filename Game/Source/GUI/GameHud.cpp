#include "GameHud.h"
#include <GUI/Timer.h>
#include "SDL_log.h"
#include "../../../../../King/Match3/Lib/SDL2-2.0.3/include/SDL_rect.h"
#include "Utils/Vector.h"
#include "Utils/CTextRenderer.h"
#include "SDL_surface.h"
#include "gamestates/basestate/GameManager.h"
#include "Utils/Common.h"

GameHUD::GameHUD(CGameManager *game)
  : m_game(game)
  , m_targetTime(60)
  , m_score(0)
  , m_pause(false)
  , m_isGameOver(false)
{
  m_gameTimer = new CTimer();
  SDL_assert(m_gameTimer != nullptr);
  m_gameTimer->Init(this, 60, &GameHUD::GameOver);
  for (int i = 0; i < 16; i++)
  {
    bubble b = bubble(i,new CTextRenderer(m_game->GetRenderer()));
    m_freeBubbleList.push_back(b);
  }
  m_timertext = new CTextRenderer(m_game->GetRenderer());
  SDL_assert(m_timertext != nullptr);
  m_timertext->SetColor(255, 0, 0);
}

GameHUD::~GameHUD()
{
  m_freeBubbleList.clear();
  if (m_gameTimer != nullptr)
    delete m_gameTimer;
  delete m_timertext;
}

void GameHUD::Update(float dt)
{
  if (!m_pause)
    m_gameTimer->Tick(dt);
}
void GameHUD::Draw()
{
  m_timertext->DrawText(m_game->GetFont("timer_font"), std::to_string(m_gameTimer->GetRemainingTime()), Vector2i(50, 50));
  m_timertext->DrawText(m_game->GetFont("score_font"), std::to_string(m_score), Vector2i(50, 150));
  if (m_showScoreBubble)
  {
    for (auto it : m_freeBubbleList)
    {
      if (it.m_active)
        it.m_text->DrawText(m_game->GetFont("bubble_font"));
    }
  }
}

void GameHUD::GameOver()
{
  m_isGameOver = true;
  m_game->SetGameSettings(m_score);
  Pause();
}

void GameHUD::SetupScoreBubble(std::vector<MatchInfo> match_info_list)
{
  m_showScoreBubble = true;
  for (int i = 0; i < match_info_list.size(); i++)
  {
    m_score += match_info_list[i].score;
    ActivateBubble(match_info_list[i]);
  }
}
void GameHUD::Pause() { m_gameTimer->Pause(); }
void GameHUD::Resume() { if (m_gameTimer->GetRemainingTime() > 0) m_gameTimer->Resume(); }
bool GameHUD::IsGameOver( ) { return m_isGameOver; }
void GameHUD::SetScore(int score) { m_score = score; }
void GameHUD::HideBubbles(){ m_showScoreBubble = false; }

void GameHUD::DeactiveteBubble()
{
  for (int i = 0; i < m_freeBubbleList.size(); i++)
  {
    m_freeBubbleList[i].m_active = false;
  }
}

void GameHUD::ActivateBubble(MatchInfo match_info)
{
  bool found = false;
  for (int i = 0; i < m_freeBubbleList.size(); i++)
  {
    if (!m_freeBubbleList[i].m_active)
    {
      bubble b = m_freeBubbleList[i];
      b.m_text->SetPosition(Utils::GetScreenPosFromIndex(match_info.index));
      b.m_text->SetText(std::to_string(match_info.score));
      b.m_text->SetColor(Utils::GetColor(match_info.color));
      m_freeBubbleList[i].m_active = true;
      found = true;
    }
  }
  if (!found)
  {
    bubble b = bubble(m_freeBubbleList.size(), /*timer*/ new CTextRenderer(m_game->GetRenderer()));
    b.m_text->SetPosition(Utils::GetScreenPosFromIndex(match_info.index));
    b.m_text->SetText(std::to_string(match_info.score));
    b.m_text->SetColor(Utils::GetColor(match_info.color));
    m_freeBubbleList.push_back(b);
  }
}