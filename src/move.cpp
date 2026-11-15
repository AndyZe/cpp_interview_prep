#include <iostream>
#include <list>
#include <vector>

// An example of std::move()

int main() {
  // A large vector that would be inefficient to copy
  std::vector<double> my_vec(20);
  my_vec.at(0) = 5;
  my_vec.at(1) = 6;

  std::list<std::vector<double>> my_list;
  my_list.push_front({0});
  // my_vec will be the second element in the list
  my_list.push_back(std::move(my_vec));

  // Expect to see 0 here
  std::cout << my_list.begin()->at(0) << std::endl;
  // Expect the elements of my_vec here
  auto it2 = my_list.begin();
  std::advance(it2, 1);
  std::cout << it2->at(0) << ", " << it2->at(1) << std::endl;
  return 0;
}
