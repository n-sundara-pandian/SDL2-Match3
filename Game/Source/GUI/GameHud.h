#ifndef GAMEHUD_H
#define GAMEHUD_H

#include <Utils/CTextRenderer.h>
#include <Match3/CBoard.h>
#include <list>

class CGameManager;
class CTimer;


class GameHUD
{
public:
  
  struct bubble
  {
    int m_id;
    CTimer *m_timer;
    CTextRenderer *m_text;
    bool m_active;
    bubble(int id, CTimer *timer, CTextRenderer *text)
      : m_timer(timer)
      , m_text(text)
      , m_id(id)
      , m_active(false)
    {}
  };
  typedef void (GameHUD::*CallBack)( );

public:
  GameHUD(CGameManager *game);
  void Update(float dt);
  void Draw();
  void SetupScoreBubble(std::vector<MatchInfo> match_info_list);
  void HideBubbles();
  void Pause();
  void Resume();
  void SetScore(int score);
  void GameOver();
  bool IsGameOver();
  void DeactiveteBubble();

private:
  std::vector<bubble> m_freeBubbleList;

  CGameManager *m_game;
  CTimer *m_gameTimer;  
  CTextRenderer *m_timertext;
  float m_targetTime;
  int m_score;
  bool m_pause;
  bool m_isGameOver;
  bool m_showScoreBubble;
private:
  void TimerCallback(){}
  void ActivateBubble(MatchInfo match_info);
};

#endif // !GAMEHUD_H
