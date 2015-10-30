#ifndef CBOARD_H
#define CBOARD_H
#include <vector>
#include <Utils/CSprite.h>
#include <Match3/CItem.h>

class CGameManager;
class CRenderer;

class CBoard
{
public:
  CBoard(){}
  CBoard(CRenderer* renderer);
  void GenerateBoard();
  void Draw();

private:
  std::vector<CItem> m_itemList;
  std::vector<CSprite> m_spriteList;
  CRenderer *m_renderer;
  int m_boardSize;
  int m_currentItem;
};

#endif // CBOARD_H
