#include <iostream>

// Given three 2D points, compute triangle area with the cross product, |(B−A) × (C−A)| / 2.

struct Point
{
  float x;
  float y;
};

struct Vector
{
  float x;
  float y;
};

float cross_produt(const Vector a, const Vector b)
{
  return a.x * b.y - a.y * b.x;
}

float triangle_area(const Point a, const Point b, const Point c)
{
  Vector b_minus_a(b.x - a.x, b.y - a.y);
  Vector c_minus_a(c.x - a.x, c.y - a.y);
  float cross = cross_produt(b_minus_a, c_minus_a);
  return std::abs(cross) / 2;
}

int main() {
  Point p1(0, 0);
  Point p2(1, 1);
  Point p3(1, 2);

  std::cout << triangle_area(p1, p2, p3) << std::endl;

  return 0;
}