
#ifndef SPRITE_H
#define SPRITE_H

#include <chrono>
#include <string>
#include <SDL.h>
#include <Utils/Vector.h>
#include <Utils/CRenderer.h>

class CRenderer;

class CSprite {
public:
  static CSprite * CreateSprite(CRenderer* graphics, const std::string& file_name, Vector2f position, Vector2i size);
  virtual ~CSprite() {};
  virtual void update() {}
  void draw(const Vector2f& pos) const;
  void draw();
  void SetTexture(const std::string& file_name);
  void SetPosition(Vector2f v);
private:
  CRenderer *m_renderer;
  SDL_Texture *m_Texture;
  Vector2f m_Position;
private:
  CSprite(CRenderer* graphics, const std::string& file_name, Vector2f position, Vector2i size);

protected:
  SDL_Rect m_SrcRect;
};

#endif /* SPRITE_H */