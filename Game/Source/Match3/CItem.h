#ifndef CITEM_H
#define CITEM_H
#include <Utils/CSprite.h>
#include <Utils/CAABB.h>

class CGameManager;
class CRenderer;

class CItem
{
public:
  enum class Color
  {
    Red,
    Blue,
    Green,
    Yellow,
    Purple
  };
  enum class State
  {
    Clean,
    Dirty
  };
public:
  CItem(Color color);
  void Update(float dt);
  void ChangeColor();
  void SetColor(Color c) { m_color = c; }
  void SetState(State s) { m_state = s; }
  Color GetColor() { return m_color; }
  State GetState() { return m_state; }
private:
  Color m_color;
  State m_state;
};
#endif