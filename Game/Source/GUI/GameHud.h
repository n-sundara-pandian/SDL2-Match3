#ifndef GAMEHUD_H
#define GAMEHUD_H

#include <Utils/CTextRenderer.h>

class CGameManager;
class CTimer;


class GameHUD
{
public:
  typedef void (GameHUD::*CallBack)(void);

public:
  GameHUD(CGameManager *game);
  void Update(float dt);
  void Draw();
  void Pause();
  void Resume();
  void GameOver();
  bool IsGameOver();
private:

  CGameManager *m_game;
  CTimer *m_timer;
  CTextRenderer *m_timertext;
  float m_targetTime;
  int m_score;
  bool m_pause;
  bool m_isGameOver;
};

#endif // !GAMEHUD_H
