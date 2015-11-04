#include <GUI/Timer.h>

CTimer::CTimer()
  : m_elapsedTime(0)
  , m_pause(true)
{

}
void CTimer::Init(GameHUD *gamehud, float target_time, GameHUD::CallBack call_back)
{
  m_gamehud = gamehud;
  m_targetTime = target_time;
  m_callback = call_back;
}
void CTimer::Tick(float dt)
{
  if (!m_pause)
  {
    m_elapsedTime += dt;
    if (m_elapsedTime > m_targetTime)
      (m_gamehud->*m_callback)();
  }
}

int CTimer::GetRemainingTime()
{
  return m_targetTime - static_cast<int>(m_elapsedTime);
}