#include <Utils/CTextRenderer.h>
CTextRenderer::CTextRenderer(CRenderer *renderer)
  : m_renderer(renderer)
{
  SetColor(255, 255, 255);
}

//Print the designated string at the specified coordinates
void CTextRenderer::DrawText(TTF_Font* font, std::string str, Vector2i pos)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, str.c_str(), m_color);
    SDL_Texture *texture = m_renderer->CreateTexture(surface);
    m_renderer->Render(texture, pos.x, pos.y);
    SDL_FreeSurface(surface);
}
void CTextRenderer::DrawText(TTF_Font* font, std::string str)
{
  DrawText(font, str, m_position);
}

void CTextRenderer::DrawText(TTF_Font* font)
{
  DrawText(font, m_text, m_position);
}

void CTextRenderer::SetColor(SDL_Color c)
{
  m_color = c;
}

void CTextRenderer::SetColor(int r, int g, int b, int a )
{
  m_color.r = r;
  m_color.g = g;
  m_color.b = b;
  m_color.a = a;
}
