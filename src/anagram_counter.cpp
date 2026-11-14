#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Implement a function which takes a list of words as an argument and finds all anagrams within the list.
// Anagrams are words which contain the exact same letters, like CREATED/CATERED/REACTED.

// Create a vector for each group of 2 or more anagrams, then return the vector of all groups.
// You can put the results in any order.

bool is_anagram(std::string a, std::string b)
{
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  return a == b;   // "STOP" -> "OPST", "TOPS" -> "OPST"
}

// Assumes all capital letters
std::vector<std::vector<std::string>> find_groups(const std::vector<std::string>& input_words)
{
  std::vector<std::string> sorted_input = input_words;

  std::vector<std::vector<std::string>> output_anagrams;

  // Sort from shortest to longest
  std::sort(sorted_input.begin(), sorted_input.end(), [](const std::string& a, const std::string& b) {
      return a.size() < b.size();
  });

  // Same-length groups of words
  std::vector<std::pair<uint /* word length*/, std::vector<std::string> /* words */>> same_length_groups;

  // For every input word
  std::cout << "Sorted input:" << std::endl;
  for (size_t word = 0; word < sorted_input.size(); ++word)
  {
    static size_t length = 0;
    // This is a new length, so add to same_length_groups
    if (sorted_input.at(word).size() > length)
    {
      length = sorted_input.at(word).size();
      auto new_pair = std::make_pair<uint, std::vector<std::string>>(length, {sorted_input.at(word)});
      same_length_groups.push_back(new_pair);
    }
    // Add to words of the same length
    else if (sorted_input.at(word).size() == length)
    {
      same_length_groups.back().second.push_back(sorted_input.at(word));
    }
    else
    {
      std::cout << "Unexpected length" << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }

  // For each word length
  for (auto word_group : same_length_groups)
  {
    std::cout << "Length: " << word_group.first << std::endl;
    output_anagrams.push_back({});

    // For each word of this length
    for (size_t word_idx = 0; word_idx < word_group.second.size(); ++word_idx)
    {
      std::cout << word_group.second.at(word_idx) << std::endl;

      output_anagrams.back().push_back(word_group.second.at(word_idx));

      // Compare to every other word of same length
      for (size_t other_word_idx = 0; other_word_idx < word_group.second.size(); ++other_word_idx)
      {
        if (other_word_idx == word_idx)
        {
          // Remove this word from future consideration
          std::erase(word_group.second, word_group.second.at(word_idx));
          continue;
        }
        if (is_anagram(word_group.second.at(word_idx), word_group.second.at(other_word_idx)))
        {
          // std::vector<std::vector<std::string>> output_anagrams;
          output_anagrams.back().push_back(word_group.second.at(other_word_idx));
          // Remove other_word from future consideration
          std::erase(word_group.second, word_group.second.at(other_word_idx));
          // Remove this word from future consideration
          std::erase(word_group.second, word_group.second.at(word_idx));
        }
        else
        {
          // Remove this word from future consideration
          std::erase(word_group.second, word_group.second.at(word_idx));
        }
      }
    }
  }

  return output_anagrams;
}

int main() {
  std::vector<std::string> input{"CREATED", "CATERED", "REACTED", "CAT"};
  auto anagram_groups = find_groups(input);
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
