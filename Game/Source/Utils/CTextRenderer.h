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
  void SetColor(int r, int g, int b, int a = 255);
private:
  CRenderer *m_renderer;
  SDL_Color m_color;
};
#endif /* TEXT_RENDERER_H*/