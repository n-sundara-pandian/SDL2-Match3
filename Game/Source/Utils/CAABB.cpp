#include <Utils/CAABB.h>
#include <algorithm>

Aabb::Aabb(const Vector2f& min, const Vector2f& max)
  : m_min(min)
  , m_max(max)
{
}
Aabb::Aabb(const Vector2i& min, const Vector2i& max)
{
  m_min.x = static_cast<float>(min.x);
  m_min.y = static_cast<float>(min.y);
  m_max.x = static_cast<float>(max.x);
  m_max.y = static_cast<float>(max.y);
}
Aabb::Aabb(float minX, float minY, float maxX, float maxY)
  : m_min(minX, minY)
  , m_max(maxX, maxY)
{
}

void Aabb::set(float minX, float minY, float maxX, float maxY)
{
  m_min.x = minX;
  m_min.y = minY;
  m_max.x = maxX;
  m_max.y = maxY;
}

bool Aabb::intersects(const Aabb& other) const
{

  if (m_max.x < other.m_min.x || m_min.x > other.m_max.x) return false;
  if (m_max.y < other.m_min.y || m_min.y > other.m_max.y) return false;
  return true;
}

bool Aabb::hasCollision(const Aabb& other) const
{
  bool result = false;

  if (intersects(other) == false) return result;

  Vector2f overlapMin(std::max(m_min.x, other.m_min.x), std::max(m_min.y, other.m_min.y));
  Vector2f overlapMax(std::min(m_max.x, other.m_max.x), std::min(m_max.y, other.m_max.y));

  if (contains(other)) result = true;

  return result;
}

bool Aabb::contains(const Aabb& other) const
{
  if (m_min.x <= other.m_min.x
    && m_min.y <= other.m_min.y
    && m_max.x >= other.m_max.x
    && m_max.y >= other.m_max.y) return true;

  return false;
}

bool Aabb::contains(const Vector2f& other) const
{
  if (m_min.x <= other.x
    && m_min.y <= other.y
    && m_max.x >= other.x
    && m_max.y >= other.y) return true;
  return false;
}
