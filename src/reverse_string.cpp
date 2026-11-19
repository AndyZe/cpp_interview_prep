#include <algorithm>
#include <cstring>
#include <iostream>

// Write a function with the following signature : void reverse(char* str) ; 

void reverse(char* str)
{
  std::reverse(str, str + std::strlen(str));
}

int main() {
  char input[] = "my_input";
  reverse(input);
  std::cout << input << std::endl;
  return 0;
}
