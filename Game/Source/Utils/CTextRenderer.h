#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include "Vector.h"
#include "CRenderer.h"

class CTextRenderer 
{

public:
  CTextRenderer(CRenderer *renderer);
  void DrawText(TTF_Font* font, std::string str, Vector2i pos);
  void DrawText(TTF_Font* font, std::string str);
  void DrawText(TTF_Font* font);
  void SetColor(int r, int g, int b, int a = 255);
  void SetPosition(Vector2i pos){ m_position = pos; }
  void SetText(const std::string &text){ m_text = text; }
  void SetColor(SDL_Color c);
private:
  CRenderer *m_renderer;
  std::string m_text;
  Vector2i m_position;
  SDL_Color m_color;
};
#endif /* TEXT_RENDERER_H*/