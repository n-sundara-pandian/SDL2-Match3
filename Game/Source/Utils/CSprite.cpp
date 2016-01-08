#include <Utils/CRenderer.h>
#include <Utils/CSprite.h>
#include "SDL_rect.h"
#include "Common.h"
CSprite::CSprite(CRenderer* graphics, const std::string& file_name, Vector2f position, int size)
{
  int tile_size = size;
  if (tile_size == -1)
    tile_size = Utils::gTileSize;
  m_SrcRect.w = tile_size;
  m_SrcRect.h = tile_size;
  m_renderer = graphics;
  SetTexture(file_name);
  SetPosition(position);
  m_currentPosition = position;
}

void CSprite::Draw(const Vector2f& pos) const
{
  const int dstx = static_cast<int>(pos.x * Utils::gTileSize);
  const int dsty = static_cast<int>(pos.y * Utils::gTileSize);

  m_renderer->Render(m_texture, dstx, dsty, &m_SrcRect);
}

void CSprite::Draw()
{
  Draw(m_currentPosition);
}

void CSprite::SetTexture(const std::string& file_name)
{ 
  m_texture = m_renderer->LoadImage(file_name.c_str(), false);
};
void CSprite::SetPosition(const Vector2f &v) 
{ 
  m_position = v; 
  m_SrcRect.x = static_cast<int>(m_position.x);
  m_SrcRect.y = static_cast<int>(m_position.y);
}

void CSprite::Update(float dt)
{
  Vector2f diff = m_currentPosition - m_position;
  m_currentPosition = m_currentPosition - diff * dt * 10;
}

void CSprite::AnimateTo(const Vector2f &v)
{
  m_position = v;
}
void CSprite::MoveTo(const Vector2f &v)
{
  m_position = v;
  m_currentPosition = v;
}

