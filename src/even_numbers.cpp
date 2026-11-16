#include <iostream>

// Write a C++ program that asks the user to enter a positive integer N and calculates the sum of all even numbers from 1 up to N (inclusive).

size_t sum_all_even_numbers(size_t n)
{
  size_t sum = 0;
  for (size_t i = 0; i < n; ++i)
  {
    if (!(i % 2))
    {
      sum += i;
    }
  }
  return sum;
}

int main() {
  size_t n = 27;
  size_t sum = sum_all_even_numbers(n);
  std::cout << sum << std::endl;
  return 0;
}
