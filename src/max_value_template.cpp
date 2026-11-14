#include <algorithm>
#include <array>
#include <iostream>

// Write a function template that returns the maximum value in an array of any type.

template<typename T, std::size_t N> T max_value(std::array<T, N> input)
{
  // TODO: handle input.size() < 1
  std::sort(input.begin(), input.end());
  return input.back();
}

int main() {
  std::array<size_t, 6> input{0, 1, 2, 3, 7, 5};
  size_t max = max_value(input);
  std::cout << max << std::endl;
  return 0;
}
