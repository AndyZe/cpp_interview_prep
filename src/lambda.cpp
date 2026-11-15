#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Use std::sort with a lambda to sort the staff by:
// Department, A to Z
// Then salary, highest first

struct Employee {
  std::string name;
  std::string department;
  int salary;
  int age;
};

int main() {
  std::vector<Employee> staff = {
    {"Alice", "Engineering", 120000, 30},
    {"Bob",   "Sales",        80000, 45},
    {"Carol", "Engineering", 120000, 28},
    {"Dave",  "Marketing",    90000, 35},
    {"Eve",   "Sales",        95000, 29},
    {"Frank", "Engineering", 150000, 40},
    {"Grace", "Marketing",    90000, 31},
  };

  // By department
  auto staff_by_department = staff;
  auto sort_dep = [](Employee& a, Employee& b) -> bool
  {
    return a.department < b.department;
  };
  std::sort(staff_by_department.begin(), staff_by_department.end(), sort_dep);
  for (const auto& e : staff_by_department)
  {
    std::cout << e.department << " | " << e.name << " | " << e.salary << "\n";
  }
  std::cout << "--" << std::endl;

  // By salary
  auto staff_by_salary = staff;
  auto sort_salary = [](Employee& a, Employee&b) -> bool
  {
    return a.salary > b.salary;
  };
  std::sort(staff_by_salary.begin(), staff_by_salary.end(), sort_salary);
  for (const auto& e : staff_by_salary)
  {
    std::cout << e.department << " | " << e.name << " | " << e.salary << "\n";
  }
  std::cout << "--" << std::endl;

  // By salary with inline lambda
  staff_by_salary = staff;
  std::sort(staff_by_salary.begin(), staff_by_salary.end(), [](Employee& a, Employee&b){return a.salary > b.salary;});
  for (const auto& e : staff_by_salary)
  {
    std::cout << e.department << " | " << e.name << " | " << e.salary << "\n";
  }
}
