
#ifndef VECTOR_H_
#define VECTOR_H_

template <typename T>
struct Vector {
  T x;
  T y;
  Vector<T>(T X = 0) : x(X), y(X) {}
  Vector<T>(T X, T Y) : x(X), y(Y) {}
  Vector<T> operator+(const Vector<T>& rhs) const
  {
    return Vector{ x + rhs.x, y + rhs.y };
  }
};

#endif /* VECTOR_H_ */