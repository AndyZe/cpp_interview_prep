#include <iostream>
#include <string>

// Write a function that expands a compressed string. The format is k[substring], which means “repeat substring k
// times. Brackets can be nested, and a string can mix plain
// letters with encoded parts.
// Examples:
// "3[a]2[bc]" -->	"aaabcbc"
// "2[a3[b]]c" -->	"abbbabbbc"

std::string expand_nested(std::string input) noexcept
{
  // Find positions of all [
  // Cache letters up to matching ]
  // Find number prior to [

  // Handle:
  // Recursion

  std::string output;

  // Iteratively trim input string
  size_t left_bracket = output.find("[");
  if (left_bracket != std::string::npos)
  {
    // Anything prior to this bracket and the number goes in the output
    output = input.substr(0, left_bracket - 2);
    // Trim the leading letters from input
    input = input.substr(left_bracket - 1, input.length() - 1);
    std::string chars_in_brackets = ;
  }
  // if no brackets remain, all remaining chars go to output
  else
  {
    output += input;
  }

  return output;
}

int main() {
  std::string test1 = "xyz3[a]2[bc]";
  std::string output = expand_nested(test1);
  std::cout << output << std::endl;
  return 0;
}
