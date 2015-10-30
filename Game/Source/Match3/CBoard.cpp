#include <Match3/CBoard.h>
#include <Utils/CRenderer.h>
#include <Utils/Common.h>

CBoard::CBoard(CRenderer* renderer)
  : m_renderer(renderer)
  , m_boardSize(8)
  , m_currentItem(0)
{
  GenerateBoard();
}

void CBoard::GenerateBoard()
{
  int m_total_items = m_boardSize * m_boardSize;
  m_itemList.reserve(m_total_items);
  m_spriteList.reserve(m_total_items);
  Vector2i sprite_size(Utils::gTileSize);
  srand(time(NULL));
  for (int i = 0; i < m_total_items; i++)
  {
    int x = i / m_boardSize;
    int y = i % m_boardSize;
    Vector2i screen_position(Utils::gBoardStartX + x, Utils::gBoardStartY + y);
    Vector2i position(x, y);
    CItem::Color rand_item = static_cast<CItem::Color>(rand() % 5);
    m_spriteList.push_back(CSprite(m_renderer, Utils::GetFileName(rand_item), screen_position, Utils::gTileSize));
    m_itemList.push_back(CItem(rand_item, position));
  }

}

void CBoard::Draw()
{
  for (auto it : m_spriteList)
    it.draw(m_renderer);
}