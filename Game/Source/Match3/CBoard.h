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
  enum class Direction
  {
    LEFT,
    RIGHT,
    UP,
    DOWN
  };
public:
  CBoard(){}
  CBoard(CRenderer* renderer);
  void GenerateBoard();
  void Draw();
  void Update(float dt);
  bool HasMatch();
  void SetItemVisible(int item, CItem::State visible);
  void AnalyseBoard();
  void RemoveMatches();

  CItem::Color GetColorAt(int index);
private:
  std::vector<CItem> m_itemList;
  std::vector<int> m_matchedItemList;
  CRenderer *m_renderer;
  int m_currentItem;
private:
  int GetStatusCount(int column_no, CItem::State status);
  int GetNextItemIndex(int cur_index, Direction dir);
};
#endif // CBOARD_H
