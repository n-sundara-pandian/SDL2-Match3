#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <map>
#include <string>

class CRenderer
{
public:
  CRenderer() {}
  CRenderer(SDL_Window *window);
  ~CRenderer();
  SDL_Texture* LoadImage(const std::string& file_name, const bool black_is_transparent = false);
  SDL_Texture* CreateTexture(SDL_Surface *surface);
  void Render(SDL_Texture *tex, const SDL_Rect dst, const SDL_Rect *clip = nullptr) const;
  void Render(SDL_Texture *tex, const int x, const int y, const SDL_Rect *clip = nullptr) const;
  void Render(SDL_Texture *tex) const;
  void Flip() const;
  void Clear() const;

protected:
  SDL_Renderer *m_SDLRenderer;
  std::map<std::string, SDL_Texture*> m_TextureList;
};

#endif /*  RENDERER_H  */