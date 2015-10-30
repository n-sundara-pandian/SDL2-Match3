
#ifndef SPRITE_H
#define SPRITE_H

#include <chrono>
#include <string>
#include <SDL.h>
#include "Utils/Vector.h"
#include "Utils/Renderer.h"

class Renderer;

struct Sprite {
  Sprite(Renderer& graphics, const std::string& file_name, Vector<int> &posiiton, Vector<int> &size);
  virtual ~Sprite() {};
  Sprite(const Sprite&) = delete;
  Sprite& operator=(const Sprite&) = delete;
  virtual void update() {}
  void draw(Renderer& graphics, const Vector<int>& pos) const;

private:
  SDL_Texture *m_Texture;

protected:
  SDL_Rect m_SrcRect;
};

#endif /* SPRITE_H */