#include <iostream>

// You’re given two rectangles on a plane. Their sides are parallel to the x and y axes. Each rectangle is described by its bottom-left corner (x1, y1) and its top-right corner (x2, y2).
// Find the total area covered by the two rectangles together. Count any overlap only once.
// Input: two triangles, each x1 y1 x2 y2
// Output: a single integer, the covered area

struct Rectangle
{
  float x1;
  float y1;
  float x2;
  float y2;
};

float covered_area(Rectangle a, Rectangle b) noexcept
{
  float area1 = (a.x2 - a.x1) * (a.y2 - a.y1);
  float area2 = (b.x2 - b.x1) * (b.y2 - b.y1);

  float overlap_w = std::max(0.0f, std::min(a.x2, b.x2) - std::max(a.x1, b.x1));
  float overlap_h = std::max(0.0f, std::min(a.y2, b.y2) - std::max(a.y1, b.y1));

  return area1 + area2 - overlap_w * overlap_h;
}

int main()
{
  Rectangle a({0, 0, 2, 2});
  Rectangle b({1, 1, 4, 4});
  float area = covered_area(a, b);
  std::cout << area << std::endl;
  return 0;
}
