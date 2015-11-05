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
  CBoard(CRenderer* renderer, GameHUD *gameHud);
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
  void CalculateNextValidTiles(int index);
  bool IsValidSelection(int selected_item);
  void Animate();
  bool IsBoardReady() { return m_boardReady; }
  void RespondToSwipe(Vector2i mouse_pos, Vector2i diff, Vector2i abs_diff);

private:
  std::vector<CItem> m_itemList;
  std::vector<CSprite*> m_spriteList;
  std::vector<CSprite*> m_hintList;
  std::vector<int> m_matchedItemList;
  std::vector<MatchInfo> m_matchInfoList;
  std::vector<int> m_nextValidSelectionList;
  GameHUD *m_gameHud;
  CRenderer *m_renderer;
  HSM *m_stateMachine;
  std::vector<int> m_selectedItemList;
  SDL_TimerID m_delayTimer;
  CPatternManager m_patternManager;
  bool m_boardReady;
  bool m_showHint;
private:
  int GetNextItemIndex(int cur_index, Direction dir);
  int ProbeNeighbour(int index, Direction direction);
  void PlaySwapAnimation(int a, int b);
  void DoItemSwap(int a, int b);
  void SetItemStatus(int index, CItem::State state);
  void ClearDirtyItems();
  void PlayAnimation(CSprite *sprite, Vector2f to);
};
#endif // CBOARD_H
