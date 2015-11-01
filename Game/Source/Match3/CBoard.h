#ifndef CBOARD_H
#define CBOARD_H
#include <vector>
#include <Utils/CSprite.h>
#include <Match3/CItem.h>

class CGameManager;
class CRenderer;
class HSM;
class CBoard
{
public:
  enum class State{
    Idle,
    OneItemSelected,
    BothItemSelected,
    SwapItem,
    ValidateMove,
    InvalidMove,
    ValidMove,
    ValidateBoard,
    GenerateBoard
  };
  typedef void (CBoard::*DoAction)(void);
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
  void Init(HSM * stateMachine);
  void GenerateBoard();
  void Draw();
  void Update(float dt);
  bool HasMatch();
  void SetItemVisible(int item, CItem::State visible);
  void AnalyseBoard();
  void ValidateMove();
  void RemoveMatches();

  CItem::Color GetColorAt(int index);
  void AddSelectedItem(int item);
  void ClearSeleceteditemList() { m_selectedItemList.clear(); }

  void ToIdle();
  void ToOneItemSelected();
  void ToBothItemSelected();
  void ToValidateMove();
  void ToInvalidMove();
  void ToValidMove();
  void ToValidateBoard();
  void ToGenerateBoard();
  void ToTestSwapItem();
  void ToActualSwap();

private:
  std::vector<CItem> m_itemList;
  std::vector<int> m_matchedItemList;
  CRenderer *m_renderer;
  HSM *m_stateMachine;
  std::vector<int> m_selectedItemList;
  SDL_TimerID m_delayTimer;
     
private:
  int GetStatusCount(int column_no, CItem::State status);
  int GetNextItemIndex(int cur_index, Direction dir);
  int ProbeNeighbour(int index, CItem::Color target_color, Direction direction);
  void DoSwap(bool reverse);


};
#endif // CBOARD_H
