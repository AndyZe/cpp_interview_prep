#include <iostream>
#include <optional>

// Write a C++ function that takes a lowercase string s and returns the index of the first character that does not
// repeat anywhere in the string. If every character repeats, return -1.

int first_nonrepeat_character(const std::string& s)
{
  // count each character
  for (size_t char_idx = 0; char_idx < s.length() - 1; ++char_idx)
  {
    size_t letter_count = 1;
    for (size_t next_idx = char_idx + 1; next_idx < s.length(); ++next_idx)
    {
      if (s[char_idx] == s[next_idx])
      {
        ++letter_count;
      }
    }
    if (letter_count == 1)
    {
      return char_idx;
    }
  }
  return -1;
}

int main() {
  std::string input{"test"};
  int first_nonrepeated_char = first_nonrepeat_character(input);
  if (first_nonrepeated_char >= 0)
  {
    std::cout << input[first_nonrepeated_char] << std::endl;
  }
  else
  {
    std::cout << "No repeats found" << std::endl;
  }
  return 0;
}
