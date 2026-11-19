#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Implement a function which takes a list of words as an argument and finds all anagrams within the list.
// Anagrams are words which contain the exact same letters, like CREATED/CATERED/REACTED.

// Create a vector for each group of 2 or more anagrams, then return the vector of all groups.
// You can put the results in any order.

std::vector<std::vector<std::string>> find_anagrams(const std::vector<std::string>& words) {
    std::unordered_map<std::string, std::vector<std::string>> groups;
    for (const auto& w : words) {
        std::string key = w;
        std::sort(key.begin(), key.end());
        // operator[] default-constructs an empty vector if `key` isn't in the map yet,
        // so the first word for a key starts a new group and later ones append to it.
        groups[key].push_back(w);
    }
    std::vector<std::vector<std::string>> result;
    for (auto& [key, group] : groups)
        if (group.size() >= 2) result.push_back(std::move(group));
    return result;
}

int main() {
  std::vector<std::string> input{"CREATED", "CATERED", "REACTED", "CAT"};
  auto anagram_groups = find_anagrams(input);
  std::cout << "Num anagram groups: " << anagram_groups.size() << std::endl;
  for (const auto& anagram_group : anagram_groups)
  {
    for (const auto& word : anagram_group)
    {
      std::cout << word << std::endl;
    }
    std::cout << "-" << std::endl;
  }
  return 0;
}
