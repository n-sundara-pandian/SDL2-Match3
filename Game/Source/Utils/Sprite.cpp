#include <Utils/Renderer.h>
#include <Utils/Sprite.h>
#include "SDL_rect.h"
Sprite::Sprite(Renderer& graphics, const std::string& file_name, Vector<int> &position, Vector<int> &size)
  : m_Texture{ graphics.loadImage(file_name.c_str(), true) }
{
  m_SrcRect.x = position.x;
  m_SrcRect.y = position.y;
  m_SrcRect.w = size.x;
  m_SrcRect.y = size.y;
}

void Sprite::draw(Renderer& graphics, const Vector<int>& pos) const
{
  const int dstx = pos.x * 32;
  const int dsty = pos.y * 32;
  graphics.renderTexture(m_Texture, dstx, dsty, &m_SrcRect);
}