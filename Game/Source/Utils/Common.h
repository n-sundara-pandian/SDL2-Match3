#ifndef COMMON_H
#define COMMON_H
#include <Match3/CBoard.h>
#include <Match3/CItem.h>

struct Utils
{
  public: 
  static const int gTileSize = 32;
  static const int gGridSize = 8;
  static const int gBoardStartX = 9;
  static const int gBoardStartY = 3;

  static std::string GetFileName(CItem::Color color)
  {
    switch (color)
    {
    case CItem::Color::Red:
      return "data/Red.png";
    case CItem::Color::Blue:
      return "data/Blue.png";
    case CItem::Color::Green:
      return "data/Green.png";
    case CItem::Color::Yellow:
      return "data/Yellow.png";
    case CItem::Color::Purple:
      return "data/Purple.png";
    default:
      break;
    }
  return "data/Purple.png";
  }
  static bool IsPointInGrid(Vector2f point)
  {
    Vector2f min(gBoardStartX * gTileSize, gBoardStartY * gTileSize);
    Vector2f max = min + Vector2f(gTileSize * gGridSize);
    Aabb bounding_box = Aabb(min, max);
    return bounding_box.contains(point);
  }

  static int GetTile(float mouse_x, float mouse_y)
  {
    Vector2f point(mouse_x, mouse_y);
    if (!IsPointInGrid(point))
      return -1;
    int x = (static_cast<int>(mouse_x) / gTileSize) - gBoardStartX;
    int y = (static_cast<int>(mouse_y) / gTileSize) - gBoardStartY;
    return x * gGridSize + y;
  }
  static CItem::Color GetRandomColor()
  {
    return static_cast<CItem::Color>(rand() % 5);

  }
};


#endif /* COMMON_H */