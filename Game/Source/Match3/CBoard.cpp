#include <Match3/CBoard.h>
#include <Utils/CRenderer.h>
#include <Utils/Common.h>

CBoard::CBoard(CRenderer* renderer)
  : m_renderer(renderer)
  , m_currentItem(0)
{
  GenerateBoard();
}

void CBoard::GenerateBoard()
{
  int m_total_items = Utils::gGridSize * Utils::gGridSize;
  m_itemList.reserve(m_total_items);
  Vector2i sprite_size(Utils::gTileSize);
  srand(time(nullptr));
  for (int i = 0; i < m_total_items; i++)
  {
    int x = i / Utils::gGridSize;
    int y = i % Utils::gGridSize;
    Vector2i screen_position(Utils::gBoardStartX + x, Utils::gBoardStartY + y);
    Vector2f position(x, y);
    m_itemList.push_back(CItem(m_renderer, Utils::GetRandomColor(), position));
  }
}

void CBoard::AnalyseBoard()
{
  for (int col = 0; col < Utils::gGridSize; col++)
  {
    for (int row = Utils::gGridSize - 1; row >= 0; row--)
    {
      if (m_itemList[col * Utils::gGridSize + row].GetState() == CItem::State::Active)
      {
        for (int i = Utils::gGridSize - 1; i >= row; i--)
        {
          if (m_itemList[col * Utils::gGridSize + i].GetState() == CItem::State::InActive)
          {
            m_itemList[col * Utils::gGridSize + i].SwapForMove(m_itemList[col * Utils::gGridSize + row]);
            break;
          }
        }
      }
    }
    int inactive_item_count = GetStatusCount(col, CItem::State::InActive);
    for (int row = 0; row < inactive_item_count; row++)
    {
      m_itemList[col * Utils::gGridSize + row].ChangeColor(inactive_item_count);
    }
  }  
}

void CBoard::RemoveMatches()
{
  m_matchedItemList.clear();
  std::vector<int> match_list;

//   Column Scan
  for (int col = 0; col < Utils::gGridSize; col++)
  {
    match_list.clear();
    for (int row = 0; row < Utils::gGridSize; row++)
    {
      int cur_index = col * Utils::gGridSize + row;
      int next_index = GetNextItemIndex(cur_index, Direction::DOWN);
      if (next_index == -1)
      {
        int prev_index = GetNextItemIndex(cur_index, Direction::UP);
        if (m_itemList[cur_index].GetColor() == m_itemList[prev_index].GetColor())
          match_list.push_back(cur_index);
        if (match_list.size() > 2)
          m_matchedItemList.insert(m_matchedItemList.end(), match_list.begin(), match_list.end());
        match_list.clear();
        break;
      }
      if (m_itemList[cur_index].GetColor() == m_itemList[next_index].GetColor())
        match_list.push_back(cur_index);
      else
      {
        match_list.push_back(cur_index);
        if (match_list.size() > 2)
          m_matchedItemList.insert(m_matchedItemList.end(), match_list.begin(), match_list.end());
        match_list.clear();
      }
    }
  }

  // Row Scan
  for (int row = 0; row < Utils::gGridSize; row++)
  {
    match_list.clear();
    for (int col = 0; col < Utils::gGridSize; col++)
    {
      int cur_index = col * Utils::gGridSize + row;
      int next_index = GetNextItemIndex(cur_index, Direction::RIGHT);
      if (next_index == -1)
      {
        int prev_index = GetNextItemIndex(cur_index, Direction::LEFT);
        if (m_itemList[cur_index].GetColor() == m_itemList[prev_index].GetColor())
          match_list.push_back(cur_index);

        if (match_list.size() > 2)
          m_matchedItemList.insert(m_matchedItemList.end(), match_list.begin(), match_list.end());
        match_list.clear();
        break;
      }
      if (m_itemList[cur_index].GetColor() == m_itemList[next_index].GetColor())
        match_list.push_back(cur_index);
      else
      {
        match_list.push_back(cur_index);
        if (match_list.size() > 2)
          m_matchedItemList.insert(m_matchedItemList.end(), match_list.begin(), match_list.end());
        match_list.clear();
      }
    }
  }
  SDL_Log(" %d items matched ", m_matchedItemList.size());
  for (int i = 0; i < m_matchedItemList.size(); i++)
  {
    SetItemVisible(m_matchedItemList[i], CItem::State::InActive);
  }
  AnalyseBoard();
  if (m_matchedItemList.size() > 0)
  {
    RemoveMatches();
  }
}

int CBoard::GetNextItemIndex(int cur_index, Direction dir)
{
  int result = -1;
  int row = cur_index % Utils::gGridSize;
  int col = cur_index / Utils::gGridSize;
  switch (dir)
  {
    case Direction::DOWN:
    {
      if (((cur_index + 1) % Utils::gGridSize) == 0)   // out of bound
        return -1;
      return cur_index + 1;
      break;
    }
    case Direction::UP:
    {
      if (((cur_index = 1) % Utils::gGridSize) == 0)   // out of bound
        return -1;
      return cur_index - 1;
      break;
    }
    case Direction::LEFT: 
    {
      result = (col - 1) * Utils::gGridSize + row;   // out of bound
      if (result < 0)
        return -1;
      return result;
      break;
    }
    case Direction::RIGHT:
    {
      result = (col + 1) * Utils::gGridSize + row;
      if (result >= Utils::gGridSize * Utils::gGridSize)  // out of bound
        return -1;
      return result;
      break;
    }
  }
  return result;
}

int CBoard::GetStatusCount(int column_no, CItem::State status)
{
  int matching_count = 0;
  for (int row = 0; row < Utils::gGridSize; row++)
  {
    if (m_itemList[column_no * Utils::gGridSize + row].GetState() == status)
      matching_count++;
  }
  return matching_count;
}
void CBoard::Update(float dt)
{
  for (int i = 0; i < m_itemList.size(); i++)
    m_itemList[i].Update(dt);
}
void CBoard::Draw()
{
  for (int i = 0; i < m_itemList.size(); i++)
      m_itemList[i].Draw();
}

bool CBoard::HasMatch()
{
  return false;
}
void CBoard::SetItemVisible(int item, CItem::State visible)
{
  m_itemList[item].SetState(visible);
}

CItem::Color CBoard::GetColorAt(int index)
{
  return m_itemList[index].GetColor();
}