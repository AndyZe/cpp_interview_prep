#include <algorithm>
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
    // If it repeats, drop "up to repeated" from the sliding window
    auto repeated_char = std::find(sliding_window.begin(), sliding_window.end(), input[i]);
    if (repeated_char != sliding_window.end())
    {
      // Remove up to and including the repeated char
      sliding_window.erase(sliding_window.begin(), repeated_char + 1);
      std::cout << "After removal for char " << input[i] << ": " << sliding_window << std::endl;
    }
    // Add the new char to the sliding window
    sliding_window += input[i];
  
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
