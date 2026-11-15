#include <array>
#include <iostream>
#include <utility>

// You get an array of integers nums and an integer target. Return the indices of the two numbers that add up to
// target. Each input has exactly one solution, and you can’t use the same element twice. You can return the answer
// in any order.
// Ex:
// Input: nums = [2, 7, 11, 15], target = 9
// Output: [0, 1]

template <std::size_t N>
std::pair<size_t, size_t> two_sum(const int target_value, std::array<int, N> possibilities) noexcept
{
  // Sum every number with every other number, check the sum

  for (size_t i = 0; i < possibilities.size(); ++i)
  {
    for (size_t j = 0; (j < possibilities.size()) && (j != i); ++j)
    {
      if (possibilities[i] + possibilities[j] == target_value)
      {
        return {i, j};
      }
    }
  }

  // TODO: error handling if we get here, this shouldn't happen
  return {0, 0};
}

int main() {
  std::array<int, 4> inputs{2, 7, 11, 15};
  auto result = two_sum(9, inputs);
  std::cout << result.first << "  " << result.second << std::endl;
  return 0;
}
