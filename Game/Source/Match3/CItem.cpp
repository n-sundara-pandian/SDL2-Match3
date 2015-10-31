
#include <Match3/CItem.h>
#include <Utils/Common.h>

CItem::CItem(CRenderer *renderer, Color color, Vector2f pos) : m_color(color)
, m_status(State::Active)
{
  Vector2f screen_position(Utils::gBoardStartX + pos.x, Utils::gBoardStartY + pos.y);
  m_position = screen_position;
  m_currentPosition = m_position;
  m_sprite = CSprite::CreateSprite(renderer, Utils::GetFileName(color), screen_position, Utils::gTileSize);
  m_currentPosition.y -= 5;
}

void CItem::Draw()
{
  if (m_status == State::Active) 
    m_sprite->draw();
}

void CItem::Update(float dt)
{
  if (m_currentPosition.y < m_position.y)
    m_currentPosition.y += (dt * 10);
  else
    m_currentPosition = m_position;
  m_sprite->SetPosition(m_currentPosition);
}

void CItem::SwapForMove(CItem &other)
{
  CItem temp = other;
  other.m_color = m_color;
  other.m_sprite->SetTexture(Utils::GetFileName(m_color));
  other.m_currentPosition = m_currentPosition;
  other.m_status = m_status;
  m_color = temp.m_color;
  m_currentPosition = temp.m_currentPosition;
  m_status = temp.m_status;
  m_sprite->SetTexture(Utils::GetFileName(m_color));
}

void CItem::ChangeColor(int adjust_position)
{
  m_status = State::Active;
  m_color = Utils::GetRandomColor();
  m_sprite->SetTexture(Utils::GetFileName(m_color));
  m_currentPosition.y = m_position.y - adjust_position;
}