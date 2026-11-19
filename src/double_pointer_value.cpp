#include <iostream>

// Write a function that takes a pointer to an integer and doubles its value.

void double_pointer_value(int* int_ptr)
{
  (*int_ptr) *= 2;
}

int main() {
  int my_int = 3;
  double_pointer_value(&my_int);
  std::cout << my_int << std::endl;
  return 0;
}
