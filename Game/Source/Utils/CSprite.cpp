#include <Utils/CRenderer.h>
#include <Utils/CSprite.h>
#include "SDL_rect.h"
CSprite::CSprite(CRenderer* graphics, const std::string& file_name, Vector2i position, Vector2i size)
{
  m_SrcRect.w = size.x;
  m_SrcRect.h = size.y;
  SetTexture(graphics, file_name);
  SetPosition(position);
}

void CSprite::draw(CRenderer* graphics, const Vector2i& pos) const
{
  const int dstx = pos.x * m_SrcRect.w;
  const int dsty = pos.y * m_SrcRect.h;
  graphics->renderTexture(m_Texture, dstx, dsty, &m_SrcRect);
}

void CSprite::draw(CRenderer* graphics)
{
  draw(graphics, m_Position);
}

void CSprite::SetTexture(CRenderer* graphics, const std::string& file_name)
{ 
  m_Texture = graphics->loadImage(file_name.c_str(), false);
};
void CSprite::SetPosition(Vector2i v) 
{ 
  m_Position = v; 
  m_SrcRect.x = m_Position.x;
  m_SrcRect.y = m_Position.y;
}
