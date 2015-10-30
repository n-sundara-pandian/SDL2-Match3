#ifndef COMMON_H
#define COMMON_H

struct Utils
{
  public: 
  static const int gTileSize = 32;
  static const int gBoardStartX = 9;
  static const int gBoardStartY = 3;
  static std::string GetFileName(Item::Color color)
  {
    switch (color)
    {
    case Item::Color::Red:
      return "data/Red.png";
    case Item::Color::Blue:
      return "data/Blue.png";
    case Item::Color::Green:
      return "data/Green.png";
    case Item::Color::Yellow:
      return "data/Yellow.png";
    case Item::Color::Purple:
      return "data/Purple.png";
    default:
      break;
    }
  return "data/Purple.png";
  }
};


#endif /* COMMON_H */