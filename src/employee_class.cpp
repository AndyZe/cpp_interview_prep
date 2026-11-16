// Problem: A company has three kinds of employees, and each kind is paid differently:

// Type	Monthly pay
// Salaried	annualSalary / 12
// Hourly	hourlyRate × hours for the first 160 hours, then 1.5 × hourlyRate for each hour over 160
// Commissioned	baseMonthly + commissionRate × totalSales

// Implement the Payroll class:

// void addSalaried(int id, double annualSalary)
// void addHourly(int id, double hourlyRate)
// void addCommissioned(int id, double baseMonthly, double commissionRate)
// bool logHours(int id, double hours): adds hours worked this month. Returns false and does nothing if the employee isn’t hourly.
// bool recordSale(int id, double amount): adds a sale this month. Returns false and does nothing if the employee isn’t commissioned.
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

int main() {
  return 0;
}