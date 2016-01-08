#ifndef COMMON_H
#define COMMON_H
#include <Match3/CBoard.h>
#include <Match3/CItem.h>
#include <vector>

struct Utils
{
  public: 
  static const int gTileSize = 32;
  static const int gGridSize = 8;
  static const int gStartCol = 9;
  static const int gStartRow = 3;
  static const int gHintTime = 5;

  static std::string GetFileName(CItem::Color color)
  {
    switch (color)
    {
    case CItem::Color::Red:
      return "data/Cupcake.png";
    case CItem::Color::Blue:
      return "data/Danish.png";
    case CItem::Color::Green:
      return "data/Macaroon.png";
    case CItem::Color::Yellow:
      return "data/SugarCookie.png";
    case CItem::Color::Purple:
      return "data/Donut.png";
    default:
      break;
    }
  return "data/witch.png";
  }
  static SDL_Color GetColor(CItem::Color color)
  {
    switch (color)
    {
    case CItem::Color::Red:
      return GetColor("Red");
    case CItem::Color::Blue:
      return GetColor("Blue");
    case CItem::Color::Green:
      return GetColor("Green");;
    case CItem::Color::Yellow:
      return GetColor("Yellow");
    case CItem::Color::Purple:
      return GetColor("Purple");
    }
    return GetColor(" ");
  }
  static SDL_Color GetColor(std::string color)
  {
    SDL_Color c;
    c.r = 255; c.g = 255; c.b = 255; c.a = 255;
    if (color == "Red")  
    { c.r = 255; c.g = 0; c.b = 0; c.a = 255; }
    else if (color == "Green")
    { c.r = 0; c.g = 255; c.b = 0; c.a = 255; }
    else if (color == "Blue")
    { c.r = 0; c.g = 0; c.b = 255; c.a = 255; }
    else if (color == "Yellow")
    { c.r = 255; c.g = 255; c.b = 0; c.a = 255; }
    else if (color == "Purple")
    { c.r = 255; c.g = 0; c.b = 255; c.a = 255; }
    else if (color == "Black")
    { c.r = 0; c.g = 0; c.b = 0; c.a = 255; }
    return c;
  }
  static std::string ToString(CItem::State state, bool bshort = false)
  {
    switch (state)
    {
    case CItem::State::Clean:
      return  bshort ? "c" : "Clean";
    case CItem::State::Dirty:
      return  bshort ? "d" : "Dirty";
    }
    return "NONE";
  }
  static std::string ToString(CItem::Color color, bool bshort = false)
  {
    switch (color)
    {
    case CItem::Color::Red:
      return bshort ? "r" : "Red";
    case CItem::Color::Blue:
      return bshort ? "b" : "Blue";
    case CItem::Color::Green:
      return bshort ? "g" : "Green";
    case CItem::Color::Yellow:
      return bshort ? "y" : "Yellow";
    case CItem::Color::Purple:
      return bshort ? "p" : "Purple";
    default:
      break;
    }
    return "NONE";
  }
  static bool IsPointInGrid(Vector2f point)
  {
    Vector2f min(gStartCol * gTileSize, gStartRow * gTileSize);
    Vector2f max = min + Vector2f(gTileSize * gGridSize);
    Aabb bounding_box = Aabb(min, max);
    return bounding_box.contains(point);
  }

  static int GetTileFromScreenPosition(float mouse_x, float mouse_y)
  {
    Vector2f point(mouse_x, mouse_y);
    if (!IsPointInGrid(point))
      return -1;
    int col = (static_cast<int>(mouse_x) / gTileSize) - gStartCol;
    int row = (static_cast<int>(mouse_y) / gTileSize) - gStartRow;
    return Utils::GetIndexFromRowCol(row, col);
  }
  static CItem::Color GetRandomColor()
  {
    return static_cast<CItem::Color>(rand() % 5);
  }
  static int GetRowFromIndex(int index)
  {
    return index % Utils::gGridSize;
  }
  static int GetColFromIndex(int index)
  {
    return index / Utils::gGridSize;
  }
  static Vector2i GetScreenPosFromRowCol(int r, int c)
  {
    return(Vector2i((gStartCol + c) * gTileSize, (gStartRow + r) * gTileSize));
  }
  static Vector2i GetScreenPosFromIndex(int i)
  {
    return GetScreenPosFromRowCol(GetRowFromIndex(i), GetColFromIndex(i));
  }
  static int GetIndexFromRowCol(int row, int col)
  {
    return col * gGridSize + row;
  }
  static std::string ToString(CBoard::State state)
  {
    switch (state)
    {
    case CBoard::State::Idle: return "Idle";
    case CBoard::State::OneItemSelected: return "OneItemSelected";
    case CBoard::State::BothItemSelected: return "BothItemSelected";
    case CBoard::State::SwapItem: return "SwapItem";
    case CBoard::State::ValidateMove: return "ValidateMove";
    case CBoard::State::NonMatchingMove: return "InvalidMove";
    case CBoard::State::MatchingMove: return "ValidMove";
    case CBoard::State::ValidateBoard: return "ValidateBoard";
    case CBoard::State::GenerateBoard: return "GenerateBoard";
    }
    return "Invalid State";
  }
  static void Swap(std::vector<CItem> &item_list, int src, int trg)
  {
    CItem temp = item_list[src];
    item_list[src] = item_list[trg];
    item_list[trg] = temp;
  }
};


#endif /* COMMON_H */