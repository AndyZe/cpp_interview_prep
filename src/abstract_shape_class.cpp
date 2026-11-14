#include <iostream>
#include <cmath>
#include <memory>

// Create an abstract Shape class with a pure virtual area() method, then implement Circle and Rectangle classes using smart pointers.

class Shape
{
public:
  virtual double area() const = 0;
  virtual ~Shape() = default;
};

class Circle : public Shape
{
public:
  Circle(double radius)
  {
    radius_ = radius;
  }

  double area() const
  {
    return M_PI * radius_ * radius_;
  }

private:
  double radius_;
};

int main() {
  std::unique_ptr<Circle> circ = std::make_unique<Circle>(3);
  std::cout << circ->area() << std::endl;
  return 0;
}
