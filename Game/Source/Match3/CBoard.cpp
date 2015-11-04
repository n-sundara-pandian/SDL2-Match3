#include <Match3/CBoard.h>
#include <Utils/CRenderer.h>
#include <Utils/Common.h>
#include <Match3/HSM.h>
CBoard::CBoard(CRenderer* renderer)
  : m_renderer(renderer)
  , m_boardReady(false)
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
  m_spriteList.reserve(m_total_items);
  Vector2i sprite_size(Utils::gTileSize);
  srand(time(nullptr));
  for (int i = 0; i < m_total_items; i++)
  {
    int row = Utils::GetRowFromIndex(i);
    int col = Utils::GetColFromIndex(i);
    Vector2f screen_position(Utils::gStartCol + col, Utils::gStartRow + row - 10);
    Vector2f position(col, row);
    CItem::Color c = Utils::GetRandomColor();
    m_itemList.push_back(CItem(c));
    m_spriteList.push_back(CSprite::CreateSprite(m_renderer, Utils::GetFileName(c), screen_position));
  }
  m_stateMachine->Go(State::ValidateBoard);
}

void CBoard::RemoveMatches()
{
  m_matchedItemList.clear();
  std::vector<int> match_list;
  for (int col = 0; col < Utils::gGridSize; col++)
  {
    match_list.clear();
    for (int row = 0; row < Utils::gGridSize; row++)
    {
      int cur_index = Utils::GetIndexFromRowCol(row, col);
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
  for (int row = 0; row < Utils::gGridSize; row++)
  {
    match_list.clear();
    for (int col = 0; col < Utils::gGridSize; col++)
    {
      int cur_index = Utils::GetIndexFromRowCol(row, col);
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
  //std::map<int, int> match_table;
  for (int i = 0; i < m_matchedItemList.size(); i++)
  {
    int col = Utils::GetColFromIndex(m_matchedItemList[i]);
    int row = Utils::GetRowFromIndex(m_matchedItemList[i]);
    //match_table[col]++ ;
    SetItemStatus(m_matchedItemList[i], CItem::State::Dirty);
    //m_spriteList[m_matchedItemList[i]]->MoveTo(Vector2f(col + Utils::gStartCol, Utils::gStartRow - match_table[col]));
  }

  if (m_matchedItemList.size() > 0)
    m_stateMachine->Go(State::FallDown,0.2f);
  else
    m_stateMachine->Go(State::Idle);
}

void CBoard::FallDown()
{
  for (int col = 0; col < Utils::gGridSize; col++)
  {
    for (int row = Utils::gGridSize - 1; row >= 0; row--)
    {
      int cur_index = Utils::GetIndexFromRowCol(row, col);
      if (m_itemList[cur_index].GetState() == CItem::State::Clean)
      {
        int target_index = cur_index;
        int next_index = cur_index;
        for (int i = row; i < Utils::gGridSize; i++)
        {
          next_index = GetNextItemIndex(next_index, Direction::DOWN);
          if (next_index == -1)
            break;
          if (m_itemList[next_index].GetState() == CItem::State::Clean)
            break;
          target_index = next_index;
        }
        int r = Utils::GetRowFromIndex(target_index);
        int c = Utils::GetColFromIndex(target_index);
        PlayAnimation(m_spriteList[cur_index], Vector2f(Utils::gStartCol + c, Utils::gStartRow + r));
        Utils::Swap(m_itemList, cur_index, target_index);
      }
    }
  }
}

void CBoard::ClearDirtyItems()
{
  for (int col = 0; col < Utils::gGridSize; col++)
  {
    for (int row = Utils::gGridSize - 1; row >= 0; row--)
    {
      int cur_index = Utils::GetIndexFromRowCol(row, col);
      if (m_itemList[cur_index].GetState() == CItem::State::Dirty)
      {
        m_itemList[cur_index].ChangeColor();
        m_spriteList[cur_index]->SetTexture(Utils::GetFileName(m_itemList[cur_index].GetColor()));
        m_spriteList[cur_index]->MoveTo(Vector2f(col + Utils::gStartCol, Utils::gStartRow - 10));
        m_itemList[cur_index].SetState(CItem::State::Clean);
        PlayAnimation(m_spriteList[cur_index],Vector2f(col + Utils::gStartCol, Utils::gStartRow + row));

      }
    }
  }  
}

int CBoard::GetNextItemIndex(int cur_index, Direction dir)
{
  int row = Utils::GetRowFromIndex(cur_index);
  int col = Utils::GetColFromIndex(cur_index);
  switch (dir)
  {
    case Direction::DOWN:
    {
      if ((row + 1) >= Utils::gGridSize) return -1; // out of bound
      return Utils::GetIndexFromRowCol(row + 1, col);
    }
    case Direction::UP:
    {
      if ((row - 1) < 0) return -1; // out of bound
      return Utils::GetIndexFromRowCol(row - 1, col);
    }
    case Direction::LEFT: 
    {
      if ((col - 1) < 0) return -1;
      return Utils::GetIndexFromRowCol(row, col - 1);
    }
    case Direction::RIGHT:
    {
      if ((col + 1) >= Utils::gGridSize) return -1;
      return Utils::GetIndexFromRowCol(row, col + 1);
    }
  }
  return -1;
}

void CBoard::Update(float dt)
{
  for (int i = 0; i < m_itemList.size(); i++)
  {
    m_itemList[i].Update(dt);
    m_spriteList[i]->Update(dt);
  }
}

void CBoard::Draw()
{
  for (int i = 0; i < m_spriteList.size(); i++)
  {
    if (m_itemList[i].GetState() == CItem::State::Clean)
      m_spriteList[i]->Draw();
  }
}

void CBoard::Animate()
{
  for (int i = 0; i < m_spriteList.size(); i++)
  {
    int row = Utils::GetRowFromIndex(i);
    int col = Utils::GetColFromIndex(i);
    Vector2f screen_position(Utils::gStartCol + col, Utils::gStartRow + row);
    PlayAnimation(m_spriteList[i], screen_position);
  }
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

void CBoard::ToIdle() 
{ 
  if (!m_boardReady)
  {
    m_boardReady = true;
    Animate();
  }
  //for (int i = 0; i < m_itemList.size(); i++)
  //{
  //  m_spriteList[i]->SetTexture(Utils::GetFileName(m_itemList[i].GetColor()));
  //  m_itemList[i].SetState(CItem::State::Clean);
  //}
}
void CBoard::OnOneSelected() {}

void CBoard::OnBothItemSelected() 
{   
  m_stateMachine->Go(State::SwapItem); 
}

void CBoard::OnMakeMove() 
{
  PlaySwapAnimation(m_selectedItemList[0], m_selectedItemList[1]);
  m_stateMachine->Go(State::ValidateMove, 0.2f);
}

void CBoard::ToActualSwap() {
  SyncItemToPosition(m_selectedItemList[0], true);
  SyncItemToPosition(m_selectedItemList[1], true);
  m_selectedItemList.clear();
  m_stateMachine->Go(State::ValidateBoard);
}

void CBoard::ToValidateMove() { 
  ValidateMove(); 
}
void CBoard::ToInvalidMove() 
{ 
  PlaySwapAnimation(m_selectedItemList[0], m_selectedItemList[1]);
  m_selectedItemList.clear();
  m_stateMachine->Go(State::Idle);
}
void CBoard::ToValidMove() { }
void CBoard::ToValidateBoard() 
{ 
  RemoveMatches(); 
}

void CBoard::ToFallDown()
{
  FallDown();
  ClearDirtyItems();
  Utils::printBoard(m_itemList);
  m_stateMachine->Go(State::GenerateBoard);
};
void CBoard::ToSyncBoard() 
{
  for (int i = 0; i < m_itemList.size(); i++)
  {
    SyncItemToPosition(i, false);
    m_itemList[i].SetState(CItem::State::Clean);
  }
  m_stateMachine->Go(State::ValidateBoard, 0.1f);
};

void CBoard::SyncItemToPosition(int i, bool bmove)
{
  int col = Utils::GetColFromIndex(i);
  int row = Utils::GetRowFromIndex(i);
  m_spriteList[i]->SetTexture(Utils::GetFileName(m_itemList[i].GetColor()));
  if (bmove)
    m_spriteList[i]->MoveTo(Vector2f(col + Utils::gStartCol, Utils::gStartRow + row));
  else
    PlayAnimation(m_spriteList[i], Vector2f(col + Utils::gStartCol, Utils::gStartRow + row));
}
void CBoard::ToGenerateBoard() 
{ 
  m_stateMachine->Go(State::SyncBoard);
}

void CBoard::ValidateMove()
{
  if (m_selectedItemList.size() != 2)
    SDL_Log(" More than two items in selection");
  Utils::Swap(m_itemList, m_selectedItemList[0], m_selectedItemList[1]);
  for (int i = 0; i < 2; i++)
  {
    int match_count = 0;
    int current_index = m_selectedItemList[i];
    match_count = ProbeNeighbour(current_index,  Direction::LEFT) + ProbeNeighbour(current_index,  Direction::RIGHT) + 1;
    if (match_count <= 2)
      match_count = ProbeNeighbour(current_index,  Direction::UP) + ProbeNeighbour(current_index,  Direction::DOWN) + 1;
    if (match_count > 2)
    {
      m_stateMachine->Go(State::MatchingMove);
      return;
    }
  }
  Utils::Swap(m_itemList, m_selectedItemList[0], m_selectedItemList[1]);
  m_stateMachine->Go(State::NonMatchingMove);
}
int CBoard::ProbeNeighbour(int current_index, Direction direction)
{
  CItem::Color target_color = m_itemList[current_index].GetColor();
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
bool CBoard::IsValidSelection(int selected_item)
{
  if (m_selectedItemList.size() != 1)
    return false;
  for (int i = 0; i < m_nextValidSelectionList.size(); i++)
  {
    if (m_nextValidSelectionList[i] == selected_item)
      return true;
  }
  return false;
}
void CBoard::CalculateNextValidTiles(int index)
{
  m_nextValidSelectionList.clear();
  if (GetNextItemIndex(index, Direction::LEFT) != -1) m_nextValidSelectionList.push_back(GetNextItemIndex(index, Direction::LEFT));
  if (GetNextItemIndex(index, Direction::RIGHT) != -1) m_nextValidSelectionList.push_back(GetNextItemIndex(index, Direction::RIGHT));
  if (GetNextItemIndex(index, Direction::UP) != -1) m_nextValidSelectionList.push_back(GetNextItemIndex(index, Direction::UP));
  if (GetNextItemIndex(index, Direction::DOWN) != -1) m_nextValidSelectionList.push_back(GetNextItemIndex(index, Direction::DOWN));
}
void CBoard::PlaySwapAnimation(int a, int b)
{
  Vector2f temp = m_spriteList[a]->GetPosition();
  PlayAnimation( m_spriteList[a], m_spriteList[b]->GetPosition());
  PlayAnimation( m_spriteList[b], temp);
}
void CBoard::SetItemStatus(int index, CItem::State state)
{
  m_itemList[index].SetState(state);
}

void CBoard::PlayAnimation(CSprite *sprite, Vector2f to)
{
  if (m_boardReady)
    sprite->AnimateTo(to);
}
