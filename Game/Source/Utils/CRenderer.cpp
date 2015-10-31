#include <SDL.h>
#include <SDL_image.h>
#include "Utils/CRenderer.h"


CRenderer::CRenderer(SDL_Window *window) :
m_SDLRenderer{ SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) },
m_TextureList()
{
  SDL_assert(m_SDLRenderer != nullptr);
  //SDL_RenderSetLogicalSize(m_SDLRenderer, window->, 480);
}

CRenderer::~CRenderer()
{
  for (auto& kv : m_TextureList) {
    SDL_DestroyTexture(kv.second);
  }
  SDL_DestroyRenderer(m_SDLRenderer);
}

SDL_Texture* CRenderer::loadImage(const std::string& file_name, const bool black_is_transparent)
{
  if (m_TextureList.count(file_name) == 0) 
  {
    SDL_Texture *t;
    if (black_is_transparent) 
    {
      SDL_Surface *surface = SDL_LoadBMP(file_name.c_str());
      SDL_assert(surface != nullptr);
      const Uint32 black_color = SDL_MapRGB(surface->format, 0, 0, 0);
      SDL_SetColorKey(surface, SDL_TRUE, black_color);
      t = SDL_CreateTextureFromSurface(m_SDLRenderer, surface);
      SDL_FreeSurface(surface);
    }
    else {
      t = IMG_LoadTexture(m_SDLRenderer, file_name.c_str());
    }
    SDL_assert(t != nullptr);
    m_TextureList[file_name] = t;
  }
  return m_TextureList[file_name];
}

void CRenderer::renderTexture(SDL_Texture *tex, const SDL_Rect dst, const SDL_Rect *clip) const
{
  SDL_RenderCopy(m_SDLRenderer, tex, nullptr, &dst);
}
void CRenderer::renderTexture(SDL_Texture *tex) const
{
  SDL_RenderCopy(m_SDLRenderer, tex, nullptr, nullptr);
}
void CRenderer::renderTexture(SDL_Texture *tex,const int x,  const int y,  const SDL_Rect *clip) const
{
  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  if (clip != nullptr) 
  {
    dst.w = clip->w;
    dst.h = clip->h;
  }
  else 
  SDL_QueryTexture(tex, nullptr, nullptr, &dst.w, &dst.h);  
  renderTexture(tex, dst, clip);
}

void CRenderer::flip() const
{
  SDL_RenderPresent(m_SDLRenderer);
}

void CRenderer::clear() const
{
  SDL_RenderClear(m_SDLRenderer);
}