#include <vector>

// Problem: A company has three kinds of employees, and each kind is paid differently:

// Type	Monthly pay
// Salaried	annualSalary / 12
// Hourly	hourlyRate × hours for the first 160 hours, then 1.5 × hourlyRate for each hour over 160

// Implement the Payroll class:

// void addSalaried(int id, double annualSalary)
// void addHourly(int id, double hourlyRate)
// bool logHours(int id, double hours): adds hours worked this month. Returns false and does nothing if the employee isn’t hourly.
// double getPay(int id): returns this month’s pay for one employee.
// double totalPayroll(): returns the sum of this month’s pay for all employees.
// void endMonth(): starts a new month by resetting every employee’s logged hours and sales to zero.

// Constraints:

// All ids are unique, and every call except an add* call uses an id that already exists.
// At most 1000 employees and 10⁴ calls in total.
// All amounts are non-negative. Answers within 1e-5 of the expected value are accepted.

// Design rules (the real challenge):

// Payroll must not use dynamic_cast, type tags, or switch/if chains on employee type.
// You should be able to add a new type, such as a Contractor paid per project, by writing one new subclass and one new add* method, without editing getPay, totalPayroll, or endMonth.
// Don’t leak memory. Think about whether Payroll should hold unique_ptr<Employee> or raw pointers.

class Employee
{
public:
  virtual ~Employee() = default;
  virtual bool logHours(size_t hours) = 0;
  virtual void endMonth() = 0;

private:
  size_t id_;
};

class Salaried : public Employee
{
public:
  bool logHours(size_t hours) override
  {
    return false;
  }

private:
  size_t salary_;
};

class Contractor : public Employee
{
  bool logHours(size_t hours) override
  {
    hours_ += hours;
    return true;
  }

  void endMonth() override
  {
    hours_ = 0;
  }

private:
  size_t hourly_rate_;
  size_t hours_;
};

class Payroll
{
public:
  // Add new Salaried employee
  void addSalaried(int id, double annualSalary)
  {
  }

  // Add new Hourly employee
  void addHourly(int id, double hourlyRate)
  {
  }

  // adds hours worked this month. Returns false and does nothing if the employee isn’t hourly.
  bool logHours(int id, double hours)
  {
    return true;
  }

  // returns this month’s pay for one employee.
  double getPay(int id)
  {
    // TODO
    return 0;
  }

  // returns the sum of this month’s pay for all employees
  double totalPayroll()
  {
    // TODO
    return 0;
  }

  // starts a new month by resetting every employee’s logged hours and sales to zero
  void endMonth()
  {
    for (auto employee : employees_)
    {
      employee.endMonth();
    }
  }

private:
  std::vector<Employee> employees_;
};

int main() {
  Payroll payroll;
  payroll.addHourly(0, 10);
  payroll.addSalaried(1, 20000);
  payroll.endMonth();
  return 0;
}