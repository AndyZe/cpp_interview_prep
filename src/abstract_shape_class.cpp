#include <iostream>
#include <cmath>
#include <memory>
#include <vector>

// Create an abstract Shape class with a pure virtual area() method, then implement Circle and Rectangle classes using smart pointers.

class Shape
{
public:
  virtual ~Shape() = default;
  virtual double area() const = 0;
};

class Circle : public Shape
{
public:
  Circle(double radius) : radius_(radius){}

  double area() const override
  {
    return M_PI * radius_ * radius_;
  }

private:
  double radius_;
};

class Square : public Shape
{
public:
  Square(double edge_length) : edge_length_(edge_length){}

  double area() const override
  {
    return edge_length_ * edge_length_;
  }

private:
  double edge_length_;
};

int main() {
  std::vector<std::unique_ptr<Shape>> shapes(2);
  shapes.at(0) = std::make_unique<Circle>(3);
  shapes.at(1) = std::make_unique<Square>(5);

  std::cout << shapes.at(0)->area() << std::endl;
  std::cout << shapes.at(1)->area() << std::endl;
  return 0;
}
