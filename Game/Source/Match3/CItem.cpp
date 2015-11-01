
#include <Match3/CItem.h>
#include <Utils/Common.h>

CItem::CItem(CRenderer *renderer, Color color, Vector2f pos) : m_color(color)
, m_status(State::Active)
, m_offset(Offset::MIDDLE)
, m_sendSwapCompleteEvent(false)
{
  Vector2f screen_position(Utils::gBoardStartX + pos.x, Utils::gBoardStartY + pos.y);
  m_position = screen_position;
  m_currentPosition = m_position;
  m_refPosition = m_position;
  m_sprite = CSprite::CreateSprite(renderer, Utils::GetFileName(color), screen_position, Utils::gTileSize);
  m_currentPosition.y -= 5;
  SDL_UserEvent userevent;
  userevent.type = SDL_USEREVENT;
  userevent.code = 0;
  m_evSwapComplete.type = SDL_USEREVENT;
  m_evSwapComplete.user = userevent;

}

void CItem::Draw()
{
  if (m_status == State::Active || m_status == State::Moving)
    m_sprite->draw();
}

void CItem::Update(float dt)
{
  Vector2f diff = m_refPosition - m_currentPosition;
  if (fabs(diff.x) < 0.25f && fabs(diff.y) < 0.25f)
  {
    m_currentPosition = m_refPosition;
    m_sprite->SetPosition(m_currentPosition);
    if (m_sendSwapCompleteEvent)
    {
      SDL_PushEvent(&m_evSwapComplete);
    }
    return;
  }
  if (m_currentPosition.y < m_refPosition.y)
    m_currentPosition.y += (dt * 10);
  else if (m_currentPosition.y > m_refPosition.y)
    m_currentPosition.y -= (dt * 10);

  if (m_currentPosition.x < m_refPosition.x)
    m_currentPosition.x += (dt * 10);
  else if (m_currentPosition.x > m_refPosition.x)
    m_currentPosition.x -= (dt * 10);

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

void CItem::SetRefPosition(Offset offset)
{
  m_refPosition = m_position;
  switch (offset)
  {
    case Offset::LEFT:
    {
      m_refPosition.x -= 1;
      break;
    }
    case Offset::RIGHT:
    {
      m_refPosition.x += 1;
      break;
    }
    case Offset::UP:
    {
      m_refPosition.y += 1;
      break;
    }
    case Offset::DOWN:
    {
      m_refPosition.y -= 1;
      break;
    }
  }
  m_offset = offset;
}
void CItem::SetRefPosition(Vector2f p)
{
  if (p.x < -0.1f)
    SetRefPosition(Offset::LEFT);
  else if (p.x > 0.1f)
    SetRefPosition(Offset::RIGHT);
  else if (p.y < -0.1f)
    SetRefPosition(Offset::DOWN);
  else if (p.y > 0.1f)
    SetRefPosition(Offset::UP);
  else
    SetRefPosition(Offset::MIDDLE);
}
