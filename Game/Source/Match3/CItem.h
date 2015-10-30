#ifndef CITEM_H
#define CITEM_H
#include "Utils/CSprite.h"

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
  enum class Status
  {
    Moving,
    Active,
    InActive
  };
public:
  CItem(Color color, Vector2i pos)
    : m_color(color)
    , m_status(Status::Active)
    , m_position(pos)
  {}

private:
  Vector2i m_position;
  Vector<float> m_actualPosition;
  Vector<float> m_targetPosition;
  Color m_color;
  Status m_status;
};
#endif