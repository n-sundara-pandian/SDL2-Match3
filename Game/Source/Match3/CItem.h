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
    Active,
    Moving,
    InActive
  };
public:
  CItem(CRenderer *renderer, Color color, Vector2f pos);

  State GetState() { return m_status; }
  void SetState(State status) { m_status = status; }
  void Draw();
  void Update(float dt);
  void SwapForMove(CItem &other);
  void ChangeColor(int adjust_position);
  Color GetColor(){ return m_color; }

private:
  CSprite *m_sprite;
  Vector2f m_position;
  Vector2f m_currentPosition;
  Color m_color;
  State m_status;
};
#endif