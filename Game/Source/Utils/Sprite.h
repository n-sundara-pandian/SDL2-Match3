
#ifndef SPRITE_H
#define SPRITE_H

#include <chrono>
#include <string>
#include <SDL.h>
#include "Utils/Vector.h"
#include "Utils/Renderer.h"

class Renderer;

class Sprite {
public:
  Sprite(Renderer* graphics, const std::string& file_name, Vector<int> position, Vector<int> size);
  virtual ~Sprite() {};
  virtual void update() {}
  void draw(Renderer* graphics, const Vector<int>& pos) const;
  void draw(Renderer* graphics);
  void SetTexture(Renderer* graphics, const std::string& file_name);
  void SetPosition(Vector<int> v);
private:
  SDL_Texture *m_Texture;
  Vector<int> m_Position;
protected:
  SDL_Rect m_SrcRect;
};

#endif /* SPRITE_H */