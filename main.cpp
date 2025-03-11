#include <iostream>
#include <vector>

using namespace std;

class Employee {
protected:
    int id;
    double salary;
public:
    Employee(int id, double salary) : id(id), salary(salary) {}

    Employee(const Employee& other) : id(other.id), salary(other.salary) {
        cout << "Copy constructor called" << endl;
    }
    //переміщення
    Employee(Employee&& other) noexcept : id(other.id), salary(other.salary) {
        other.id = 0;
        other.salary = 0.0;
        cout << "Move constructor called" << endl;
    }

    Employee& setSalary(double newSalary) {
        this->salary = newSalary;
        return *this;
    }

    virtual void showInfo() const {
        cout << "ID: " << id << "\nSalary: " << salary << endl;
    }

    virtual double calculate() const {
        return salary;
    }

    virtual ~Employee() {}

    // Перевантаження оператора << (дружня функція)
    friend ostream& operator<<(ostream& os, const Employee& emp) {
        os << "Employee ID: " << emp.id << "\nSalary: " << emp.salary;
        return os;
    }
};

class FulltimeEmployee : public Employee {
private:
    double bonus;
public:
    FulltimeEmployee(int id, double salary, double bonus) : Employee(id, salary), bonus(bonus) {}

    void showInfo() const override {
        cout << "Full-Time Employee: " << id << "\nSalary: " << salary << "\nBonus: " << bonus << endl;
    }

    double calculate() const override {
        return salary + bonus;
    }
};

class ParttimeEmployee : public Employee {
private:
    int hoursWorked;
    double hourlyRate;
public:
    ParttimeEmployee(int id, int hours, double rate) : Employee(id, 0), hoursWorked(hours), hourlyRate(rate) {}

    void showInfo() const override {
        cout << "Part-Time Employee ID: " << id << "\nHours Worked: " << hoursWorked << "\nHourly Rate: " << hourlyRate << endl;
    }

    double calculate() const override {
        return hoursWorked * hourlyRate;
    }
};

class PayrollManager {
private:
    vector<Employee*> employees;

public:
    void addEmployee(Employee* e) {
        employees.push_back(e);
    }

    void processPayroll() const {
        for (const auto& employee : employees) {
            employee->showInfo();
            cout << "Total Pay: " << employee->calculate() << "\n";
        }
    }

    ~PayrollManager() {
        for (auto& e : employees) {
            delete e;
        }
    }
};

int main() {
    PayrollManager manager;
    manager.addEmployee(new FulltimeEmployee(1, 3000, 500));
    manager.addEmployee(new ParttimeEmployee(2, 60, 20));

    cout << "Payroll Processing: " << endl;
    manager.processPayroll();

    return 0;
}
