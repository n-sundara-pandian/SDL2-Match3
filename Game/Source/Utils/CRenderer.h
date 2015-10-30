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
  CRenderer(const CRenderer&) = delete;
  CRenderer& operator=(const CRenderer&) = delete;
  SDL_Texture* loadImage(const std::string& file_name, const bool black_is_transparent = false);
  void renderTexture(SDL_Texture *tex, const SDL_Rect dst, const SDL_Rect *clip = nullptr) const;
  void renderTexture(SDL_Texture *tex, const int x, const int y, const SDL_Rect *clip = nullptr) const;
  void renderTexture(SDL_Texture *tex) const;
  void flip() const;
  void clear() const;

private:
  SDL_Renderer *m_SDLRenderer;
  std::map<std::string, SDL_Texture*> m_TextureList;
};

#endif /*  RENDERER_H  */