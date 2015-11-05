#include <Match3/CHint.h>
#include "Utils/Common.h"

CPatternManager::Pattern::Pattern(std::string str)
  : name(str)
{
  for (auto c : name)
    pattern.push_back(static_cast<ItemType>(c - 48));
}
std::vector<int> CPatternManager::Pattern::FindPatternAt(std::vector<int> color_list, int i, StepType t)
{
  std::vector<int> result;
  int cur_index = i;
  int color = -1;
  for (int index = 0; index < pattern.size(); index++)
  {
    ItemType itype = static_cast<ItemType> (pattern[index]);
    cur_index = GetNextIndex(cur_index, t, pattern.size() < 4);
    switch (itype)
    {
    case MustMatch:
    {
      if (cur_index == -1)
      {
        result.clear();
        return result;
      }
      if (color == -1)
      {
        color = color_list[cur_index];
        result.push_back(cur_index);
        break;
      }
      if (color != color_list[cur_index])
      {
        result.clear();
        return result;
      }
      result.push_back(cur_index);
      break;
    }
    case WildCard:
      break;
    }

  }
  return result;
}
int CPatternManager::Pattern::GetNextIndex(int index, StepType step, bool single_line_check)
{
  int result = -1;
  ScanType current_scan_type;
  switch (step)
  {
  case Left:
  {
  result = index - 1;
  current_scan_type = Horizontal;
  break;
  }
  case Right:
  {
  result = index + 1;
  current_scan_type = Horizontal;
  break;
  }
  case Up:
  {
  result = index - Utils::gGridSize;
  current_scan_type = Verticle;
  break;
  }
  case Down:
  {
  result = index + Utils::gGridSize;
  current_scan_type = Verticle;
  break;
  }
  }
  if (result == -1)
    return -1;
  if (!((result >= 0) && (result < Utils::gGridSize * Utils::gGridSize)))
  return -1;
  int r1 = Utils::GetRowFromIndex(index);
  int r2 = Utils::GetRowFromIndex(result);
  int c1 = Utils::GetColFromIndex(index);
  int c2 = Utils::GetColFromIndex(result);
  if (single_line_check)
  {
  if (current_scan_type == Horizontal && (r1 != r2))
  result = -1;
  else if (current_scan_type == Verticle && (c1 != c2))
  result = -1;
  }
  else
  {
  if (current_scan_type == Horizontal && (abs(r1 - r2) > 1))
  result = -1;
  else if (current_scan_type == Verticle && (abs(c1 - c2) > 1))
  result = -1;
  }
  return result;

}


std::string CPatternManager::ConstructTwoLinePattern(std::string base, int insert_after)
{
  for (int i = 0; i < insert_after - 1; i++)
    base += "0";
  base += "1";
  return base;
}
void CPatternManager::Init(const std::vector<int> &board)
{
  m_board = board;
  m_patternList.push_back(Pattern("1101"));
  m_patternList.push_back(Pattern("1011"));
  //m_patternList.push_back(Pattern(ConstructTwoLinePattern("011", Utils::gGridSize - 2)));
  //m_patternList.push_back(Pattern(ConstructTwoLinePattern("101", Utils::gGridSize - 1)));
  //m_patternList.push_back(Pattern(ConstructTwoLinePattern("110", Utils::gGridSize)));
}
bool CPatternManager::HasHint(int board_index, int i, StepType t)
{
  vector<int> hints = m_patternList[i].FindPatternAt(m_board, board_index, t);
  if (hints.size() > 0)
  {
    m_hintList.push_back(Hint(hints));
  }
  return hints.size() > 0;
}
void CPatternManager::ConstructHintList()
{
  m_hintList.clear();
  for (int i = 0; i < m_board.size(); i++)
  {
    for (int j = 0; j < m_patternList.size(); j++)
    {
      HasHint(i, j, StepType::Down);
      HasHint(i, j, StepType::Right);
    }
  }
}

CPatternManager::Hint CPatternManager::GetHint()
{
  if (m_hintList.size() == 0)
    return std::vector<int>();
  return m_hintList[rand() % m_hintList.size() ];
}