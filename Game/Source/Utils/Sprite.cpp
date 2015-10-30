#include <Utils/Renderer.h>
#include <Utils/Sprite.h>
#include "SDL_rect.h"
Sprite::Sprite(Renderer* graphics, const std::string& file_name, Vector<int> position, Vector<int> size)
{
  m_SrcRect.w = size.x;
  m_SrcRect.h = size.y;
  SetTexture(graphics, file_name);
  SetPosition(position);
}

void Sprite::draw(Renderer* graphics, const Vector<int>& pos) const
{
  const int dstx = pos.x * m_SrcRect.w;
  const int dsty = pos.y * m_SrcRect.h;
  graphics->renderTexture(m_Texture, dstx, dsty, &m_SrcRect);
}

void Sprite::draw(Renderer* graphics)
{
  draw(graphics, m_Position);
}

void Sprite::SetTexture(Renderer* graphics, const std::string& file_name)
{ 
  m_Texture = graphics->loadImage(file_name.c_str(), false);
};
void Sprite::SetPosition(Vector<int> v) 
{ 
  m_Position = v; 
  m_SrcRect.x = m_Position.x;
  m_SrcRect.y = m_Position.y;
}
