#include <Match3/CBoard.h>
#include <Utils/CRenderer.h>
#include <Utils/Common.h>
#include <Match3/HSM.h>
CBoard::CBoard(CRenderer* renderer)
  : m_renderer(renderer)
{
  
}

void CBoard::Init(HSM * stateMachine)
{
  m_stateMachine = stateMachine;
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
      if (((cur_index - 1) % Utils::gGridSize) == 0)   // out of bound
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

void CBoard::AddSelectedItem(int item)
{
  m_selectedItemList.push_back(item);
  if (m_selectedItemList.size() > 2)
    SDL_Log(" More than two items in selection");
}

void CBoard::ToIdle() { SDL_Log("ToIdle"); }
void CBoard::ToOneItemSelected() {}
void CBoard::ToBothItemSelected() {   m_stateMachine->Go(State::SwapItem); }
void CBoard::ToTestSwapItem() { DoSwap(false); }
void CBoard::ToActualSwap() {
  if (m_selectedItemList.size() > 2)
    SDL_Log(" More than two items in selection");
  m_itemList[m_selectedItemList[0]].SwapForMove(m_itemList[m_selectedItemList[1]]);
  m_selectedItemList.clear();
  m_stateMachine->Go(State::ValidateBoard);
}

void CBoard::ToValidateMove() { 
  ValidateMove(); 
}
void CBoard::ToInvalidMove() 
{ 
  DoSwap(true); 
  m_selectedItemList.clear();
}
void CBoard::ToValidMove() { }
void CBoard::ToValidateBoard() { SDL_Log(" To validate Board"); RemoveMatches(); }
void CBoard::ToGenerateBoard() { SDL_Log(""); }

void CBoard::DoSwap(bool reverse)
{
  if (m_selectedItemList.size() != 2)
    SDL_Log(" More than two items in selection");
  Vector2f diff = m_itemList[m_selectedItemList[1]].GetCurrentPosition() - m_itemList[m_selectedItemList[0]].GetCurrentPosition();
  if (reverse)
  {
    m_itemList[m_selectedItemList[0]].SetRefPosition(CItem::Offset::MIDDLE);
    m_itemList[m_selectedItemList[1]].SetRefPosition(CItem::Offset::MIDDLE);
  }
  else
  {
    m_itemList[m_selectedItemList[0]].SetRefPosition(diff);
    m_itemList[m_selectedItemList[1]].SetRefPosition(Vector2f() - diff);
  }
  m_itemList[m_selectedItemList[0]].SetState(CItem::State::Moving);
  m_itemList[m_selectedItemList[0]].SetSendEvent(true);
  m_itemList[m_selectedItemList[1]].SetState(CItem::State::Moving);
}

void CBoard::ValidateMove()
{
  if (m_selectedItemList.size() != 2)
    SDL_Log(" More than two items in selection");

  for (int i = 0; i < 2; i++)
  {
    int match_count = 0;
    int current_index = m_selectedItemList[i];
    CItem::Color target_color = (i == 0) ? m_itemList[m_selectedItemList[1]].GetColor() : m_itemList[m_selectedItemList[0]].GetColor();
    match_count = ProbeNeighbour(current_index, target_color, Direction::LEFT) + ProbeNeighbour(current_index, target_color, Direction::RIGHT) + 1;
    if (match_count <= 2)
      match_count = ProbeNeighbour(current_index, target_color, Direction::UP) + ProbeNeighbour(current_index, target_color, Direction::DOWN) + 1;
    if (match_count > 2)
    {
      m_stateMachine->Go(State::ValidMove);
      return;
    }
  }
  m_stateMachine->Go(State::InvalidMove);
}
int CBoard::ProbeNeighbour(int current_index, CItem::Color target_color, Direction direction)
{
  int match_count = 0;
  for (int i = 0; i < Utils::gGridSize; i++)
  {
    int next_index = GetNextItemIndex(current_index, direction);
    if (next_index == -1)
      return match_count;
    if (m_itemList[next_index].GetColor() != target_color)
      return match_count;
    match_count++;
    current_index = next_index;
    if (match_count >= 2)
      return match_count;
  }
  return match_count;
}