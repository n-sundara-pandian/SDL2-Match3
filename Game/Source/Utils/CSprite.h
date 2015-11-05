
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
  static CSprite * CreateSprite(CRenderer* graphics, const std::string& file_name, Vector2f position);
  virtual ~CSprite() {};
  virtual void Update(float dt);
  void Draw();
  void SetTexture(const std::string& file_name);
  void AnimateTo(const Vector2f &v);
  void MoveTo(const Vector2f &v);
  const Vector2f GetPosition() { return m_position; }
private:
  CRenderer *m_renderer;
  SDL_Texture *m_texture;
  Vector2f m_position;
  Vector2f m_currentPosition;


private:
  CSprite(CRenderer* graphics, const std::string& file_name, Vector2f position);
  void Draw(const Vector2f& pos) const;
  void SetPosition(const Vector2f &v);

protected:
  SDL_Rect m_SrcRect;
};

#endif /* SPRITE_H */