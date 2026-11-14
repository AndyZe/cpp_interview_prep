#include <algorithm>
#include <iostream>

// Write a C++ function that takes a lowercase string s and returns the index of the first character that does not
// repeat anywhere in the string. If every character repeats, return -1.

int first_nonrepeat_character(const std::string& s)
{
  std::string sorted = s;
  std::sort(sorted.begin(), sorted.end());
  // Compare every char to every other char
  for (int char_idx = 0; char_idx < sorted.length() - 1; ++char_idx)
  {
    // Since the string is sorted, just need to check the next idx
    if (sorted[char_idx] != sorted[char_idx + 1])
    {
      // Found a non-repeated character
      // Convert back to unsorted idx
      return std::find(s.begin(), s.end(), sorted[char_idx]) - s.begin();
    }
  }
  return -1;
}

int main() {
  std::string input{"test"};
  int first_nonrepeated_char = first_nonrepeat_character(input);
  std::cout << input[first_nonrepeated_char] << std::endl;
  return first_nonrepeated_char;
}
