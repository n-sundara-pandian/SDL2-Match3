#ifndef CAABB_H
#define CAABB_H
#include <utils/Vector.h>

class Aabb
{
public:

  Aabb() : m_min(Vector2f()), m_max(Vector2f()){}
  Aabb(const Vector2f& min, const Vector2f& max);
  Aabb(const Vector2i& min, const Vector2i& max);
  Aabb(float minX, float minY, float maxX, float maxY);

  void set(float minX, float minY, float maxX, float maxY);

  const Vector2f& min() const { return m_min; }
  const Vector2f& max() const { return m_max; }
  Vector2f& min() { return m_min; }
  Vector2f& max() { return m_max; }

  bool intersects(const Aabb& other) const;
  bool hasCollision(const Aabb& other) const;
  bool contains(const Aabb& other) const;
  bool contains(const Vector2f& other) const;
private:
  Vector2f m_min;
  Vector2f m_max;

};

#endif // CAABB_H