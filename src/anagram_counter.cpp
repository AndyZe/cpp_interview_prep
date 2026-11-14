#include <iostream>
#include <string>
#include <vector>

// Implement a function which takes a list of words as an argument and finds all anagrams within the list.
// Anagrams are words which contain the exact same letters, like CREATED/CATERED/REACTED.

// Create a vector for each group of 2 or more anagrams, then return the vector of all groups.
// You can put the results in any order.

// Assumes all capital letters
std::vector<std::vector<std::string>> find_groups(const std::vector<std::string>& input_words)
{
  return {};
}

int main() {
  std::vector<std::string> input{"CREATED", "CATERED", "REACTED"};
  auto anagram_groups = find_groups(input);
  std::cout << anagram_groups.size() << std::endl;
  return 0;
}
