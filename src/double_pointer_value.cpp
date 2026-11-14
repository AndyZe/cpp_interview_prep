#include <iostream>

// Write a function that takes a pointer to an integer and doubles its value.

void double_pointer_value(int* int_ptr)
{
  (*int_ptr) *= 2;
}

int main() {
  int my_ptr = 3;
  double_pointer_value(&my_ptr);
  std::cout << my_ptr << std::endl;
  return 0;
}
