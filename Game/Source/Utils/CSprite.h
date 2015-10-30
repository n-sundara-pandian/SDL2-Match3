
#ifndef SPRITE_H
#define SPRITE_H

#include <chrono>
#include <string>
#include <SDL.h>
#include "Utils/Vector.h"
#include "Utils/CRenderer.h"

class CRenderer;

class CSprite {
public:
  CSprite(CRenderer* graphics, const std::string& file_name, Vector2i position, Vector2i size);
  virtual ~CSprite() {};
  virtual void update() {}
  void draw(CRenderer* graphics, const Vector2i& pos) const;
  void draw(CRenderer* graphics);
  void SetTexture(CRenderer* graphics, const std::string& file_name);
  void SetPosition(Vector2i v);
private:
  SDL_Texture *m_Texture;
  Vector2i m_Position;
protected:
  SDL_Rect m_SrcRect;
};

#endif /* SPRITE_H */