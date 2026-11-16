#include <iostream>
#include <string>

// Given a string s, return the length of the longest substring that has no repeated characters. A substring has to be
// contiguous, so skipping characters isn’t allowed.

size_t find_longest(const std::string& input) noexcept
{
  std::string sliding_window;
  size_t longest_yet = 0;
  for (size_t i = 0; i < input.length(); ++i)
  {
    // Add a new char to the sliding window
    sliding_window += input[i];
    // If it repeats the first char, drop the first char from the sliding window
    if ((sliding_window.length() > 1) && (sliding_window[0] == sliding_window.back()))
    {
      sliding_window.erase(0, 1);
    }
  
    // New high score?
    if (sliding_window.length() > longest_yet)
    {
      std::cout << "New longest substring: " << sliding_window << std::endl;
      ++longest_yet;
    }
  }
  return longest_yet;
}

int main() {
  std::string input = "asdflkajsfdidflkjhfaa";
  size_t longest = find_longest(input);
  std::cout << "Longest non-repeating substring: " << longest << std::endl;
  return 0;
}
