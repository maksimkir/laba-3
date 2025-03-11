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