#ifndef HINT_H 
#define HINT_H 

#include <iostream>
#include <time.h>
#include <vector>
#include <memory>
#include <Match3/CItem.h>
using namespace std;

class CItem;
class CPatternManager
{
public:
  enum ItemType
  {
    WildCard,
    MustMatch
  };
  enum StepType
  {
    Left,
    Right,
    Up,
    Down
  };
  enum ScanType
  {
    Horizontal,
    Verticle,
  };
  struct Hint
  {
    std::vector<int> index_list;
    Hint(std::vector<int> h)
      : index_list(h)
    {}
  };
  struct Pattern
  {
    std::vector<ItemType> pattern;
    std::string name;
    Pattern(){}
    Pattern(std::string str);
    std::vector<int> FindPatternAt(std::vector<int> color_list, int i, StepType t);
    int GetNextIndex(int index, StepType step, bool single_line_check);
  };

  std::string ConstructTwoLinePattern(std::string base, int insert_after);
  CPatternManager();
  void Init(std::vector<int> board);
  bool HasHint(int board_index, int i, StepType t);
  void ConstructHintList();
  Hint GetHint();
private:
  std::vector<int> m_board;
  std::vector<Pattern> m_patternList;
  std::vector<Hint> m_hintList;
};
#endif // HINT_H