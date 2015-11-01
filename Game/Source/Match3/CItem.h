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
  enum class Offset
  {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    MIDDLE,
  };
public:
  CItem(CRenderer *renderer, Color color, Vector2f pos);

  void Draw();
  void Update(float dt);
  void SwapForMove(CItem &other);

  Color GetColor(){ return m_color; }
  void ChangeColor(int adjust_position);

  State GetState() { return m_status; }
  void SetState(State status) { m_status = status; }

  Vector2f GetCurrentPosition(){ return m_currentPosition; }
  //void SetCurrentPosition(Vector2f p) { m_currentPosition = p; }

  void SetRefPosition(Offset offset);
  void SetRefPosition(Vector2f p);
  void SetSendEvent(bool flag){ m_sendSwapCompleteEvent = flag; }

private:
  CSprite *m_sprite;
  Vector2f m_position;
  Vector2f m_currentPosition;
  Vector2f m_refPosition;
  Color m_color;
  State m_status;
  Offset m_offset;
  SDL_Event m_evSwapComplete;
  bool m_sendSwapCompleteEvent;
};
#endif