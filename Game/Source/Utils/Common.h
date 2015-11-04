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

  static int GetTile(float mouse_x, float mouse_y)
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
  static void printBoard(std::vector<CItem> &item_list)
  {
    std::string line_str = "";
    for (int row = 0; row < gGridSize; row++)
    {
      for (int col = 0; col < gGridSize; col++)
      {
        int i = GetIndexFromRowCol(row, col);
        std::string temp_str;
        temp_str += " (" + std::to_string(row) + "," + std::to_string(col) + ") " + ToString(item_list[i].GetState(), true);
        line_str += temp_str;
      }
      line_str += "\n";
      SDL_Log("%s", line_str.c_str());
      line_str = "";
    }
  }
  static void Swap(std::vector<CItem> &item_list, int src, int trg)
  {
    CItem temp = item_list[src];
    item_list[src] = item_list[trg];
    item_list[trg] = temp;
  }
/*  static void printBoard()
  {
    std::string line_str = "";
    for (int row = 0; row < gGridSize; row++)
    {
      for (int col = 0; col < gGridSize; col++)
      {
        int i = GetIndexFromRowCol(row, col);
        int c = GetColFromIndex(i);
        int r = GetRowFromIndex(i);
        std::string temp_str;
        temp_str += " (" + std::to_string(row) + "," + std::to_string(col) + ") " + std::to_string(i) + " (" + std::to_string(r) + "," + std::to_string(c) + ") ";
        line_str += temp_str;
      }
      line_str += "\n";
      SDL_Log("%s", line_str.c_str());
      line_str = "";
    }
  }*/
};


#endif /* COMMON_H */