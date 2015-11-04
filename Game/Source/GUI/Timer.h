#ifndef TIMER_H
#define TIMER_H
#include <GUI/GameHud.h>

class GameHUD;
class CTimer
{
public:
  CTimer();
  void Tick(float dt);
  void Init(GameHUD *gamehud, float target_time, GameHUD::CallBack call_back);
  void Start() { m_pause = false; }
  void Pause() { m_pause = true; }
  void Resume(){ m_pause = false; }
  int GetRemainingTime();
private:
  GameHUD *m_gamehud;
  GameHUD::CallBack m_callback;
  int m_targetTime;
  float m_elapsedTime;
  bool m_pause;
};

#endif