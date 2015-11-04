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
    NonMatchingMove,
    MatchingMove,
    ValidateBoard,
    FallDown,
    GenerateBoard,
    SyncBoard
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
  void FallDown();
  void ValidateMove();
  void RemoveMatches();

  CItem::Color GetColorAt(int index);
  void AddSelectedItem(int item);
  void ClearSeleceteditemList() { m_selectedItemList.clear(); }
  void SyncItemToPosition(int index, bool bmove);

  void ToIdle();
  void OnOneSelected();
  void OnBothItemSelected();
  void ToValidateMove();
  void ToInvalidMove();
  void ToValidMove();
  void ToValidateBoard();
  void ToGenerateBoard();
  void ToFallDown();
  void ToSyncBoard();
  void OnMakeMove();
  void ToActualSwap();
  void CalculateNextValidTiles(int index);
  bool IsValidSelection(int selected_item);
  void Animate();
  std::vector<CItem> m_itemList;

private:
  std::vector<CSprite*> m_spriteList;
  std::vector<int> m_matchedItemList;
  std::vector<int> m_nextValidSelectionList;
  CRenderer *m_renderer;
  HSM *m_stateMachine;
  std::vector<int> m_selectedItemList;
  SDL_TimerID m_delayTimer;
     
private:

  int GetNextItemIndex(int cur_index, Direction dir);
  int ProbeNeighbour(int index, Direction direction);
  void PlaySwapAnimation(int a, int b);
  void DoItemSwap(int a, int b);
  void SetItemStatus(int index, CItem::State state);
  void ClearDirtyItems();
};
#endif // CBOARD_H
