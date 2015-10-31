#include <Utils/CRenderer.h>
#include <Utils/CSprite.h>
#include "SDL_rect.h"
CSprite::CSprite(CRenderer* graphics, const std::string& file_name, Vector2f position, Vector2i size)
{
  m_SrcRect.w = size.x;
  m_SrcRect.h = size.y;
  m_renderer = graphics;
  SetTexture(file_name);
  SetPosition(position);
}

CSprite * CSprite::CreateSprite(CRenderer* graphics, const std::string& file_name, Vector2f position, Vector2i size)
{
  return new CSprite(graphics, file_name, position, size);
}

void CSprite::draw(const Vector2f& pos) const
{
  const int dstx = pos.x * m_SrcRect.w;
  const int dsty = pos.y * m_SrcRect.h;
  m_renderer->renderTexture(m_Texture, dstx, dsty, &m_SrcRect);
}

void CSprite::draw()
{
  draw(m_Position);
}

void CSprite::SetTexture(const std::string& file_name)
{ 
  m_Texture = m_renderer->loadImage(file_name.c_str(), false);
};
void CSprite::SetPosition(Vector2f v) 
{ 
  m_Position = v; 
  m_SrcRect.x = m_Position.x;
  m_SrcRect.y = m_Position.y;
}
