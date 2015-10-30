#ifndef COMMON_H
#define COMMON_H
#include <Match3/CBoard.h>
#include <Match3/CItem.h>

struct Utils
{
  public: 
  static const int gTileSize = 32;
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
};


#endif /* COMMON_H */