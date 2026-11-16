#include <iostream>
#include <string>

// Given a string s, return the length of the longest substring that has no repeated characters. A substring has to be
// contiguous, so skipping characters isn’t allowed.

size_t find_longest(const std::string& input) noexcept
{
  return 0;
}

int main() {
  std::string input = "asdflkajsfdidflkjhfaa";
  size_t longest = find_longest(input);
  std::cout << "Longest non-repeating substring: " << longest << std::endl;
  return 0;
}
