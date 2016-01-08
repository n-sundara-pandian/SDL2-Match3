#ifndef CBOARD_H
#define CBOARD_H
#include <vector>
#include <Utils/CSprite.h>
#include <Match3/CItem.h>
#include <Match3/CHint.h>

class CGameManager;
class CRenderer;
class HSM;
class GameHUD;
struct MatchInfo 
{
  CItem::Color color;
  int count;
  int index;
  int score;
  MatchInfo(CItem::Color col, int no, int i)
    : color(col)
    , count(no)
    , index(i)
  {
    score = count * 50;
  }
};
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
    SyncBoard,
    Hint
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
  ~CBoard();
  CBoard(CRenderer* renderer, shared_ptr<GameHUD> gameHud);
  void Init(HSM *stateMachine);
  void Draw();
  void Update(float dt);
  void ToIdle();
  void OnOneSelected();
  void OnBothItemSelected();
  void ToHint();
  void ToValidateMove();
  void ToInvalidMove();
  void ToValidMove();
  void ToValidateBoard();
  void ToGenerateBoard();
  void ToFallDown();
  void ToSyncBoard();
  void OnMakeMove();
  void ToActualSwap();
  void RespondToSwipe(const Vector2i &mouse_pos, const Vector2i &diff, const Vector2i &abs_diff);
  void CalculateNextValidTiles(const int &index);
  bool IsValidSelection(const int &selected_item) const;
  void AddSelectedItem(const int &item);
  void ClearSeleceteditemList() { m_selectedItemList.clear(); }
  bool IsBoardReady() { return m_boardReady; }

private:
  std::vector<CItem> m_itemList;
  std::vector<shared_ptr<CSprite>> m_spriteList;
  std::vector<shared_ptr<CSprite>> m_hintList;
  std::vector<MatchInfo> m_matchInfoList;
  std::vector<int> m_matchedItemList;
  std::vector<int> m_nextValidSelectionList;
  std::vector<int> m_selectedItemList;
  CSprite *m_tile;
  CPatternManager m_patternManager;
  shared_ptr<GameHUD> m_gameHud;
  CRenderer *m_renderer;
  HSM *m_stateMachine;
  bool m_boardReady;
  bool m_showHint;

private:
  CItem::Color GetColorAt(const int &index);
  int GetNextItemIndex(const int &cur_index, const Direction &dir) const;
  int ProbeNeighbour(int index, Direction direction);
  void GenerateBoard();
  void FallDown();
  void ValidateMove();
  void RemoveMatches();
  void PlaySwapAnimation(const int &a, const int &b);
  void DoItemSwap(int a, int b);
  void SetItemStatus(const int &index, const CItem::State &state);
  void ClearDirtyItems();
  void PlayAnimation(const weak_ptr<CSprite>sprite, const Vector2f to);
  void Animate();
  void SyncItemToPosition(const int &index, const bool &bmove);
};
#endif // CBOARD_H
