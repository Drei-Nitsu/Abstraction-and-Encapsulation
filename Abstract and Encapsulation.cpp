#include <iostream>
#include <vector>
#include <limits>
#include <string>

using namespace std;

// Abstract Base Class (Abstraction)
class Employee {
protected:
    int id;
    string name;
public:
    Employee(int id, string name) : id(id), name(name) {}
    virtual void displaySalary() const = 0; // Pure virtual function (Abstraction)
    int getId() const { return id; }
    string getName() const { return name; }
    virtual ~Employee() {}
};

// Full-time Employee
class FullTimeEmployee : public Employee {
private:
    double salary;
public:
    FullTimeEmployee(int id, string name, double salary)
        : Employee(id, name), salary(salary) {}

    void displaySalary() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Fixed Monthly Salary: $" << salary << "\n\n";
    }
};

// Part-time Employee
class PartTimeEmployee : public Employee {
private:
    double hourlyWage;
    int hoursWorked;
public:
    PartTimeEmployee(int id, string name, double hourlyWage, int hoursWorked)
        : Employee(id, name), hourlyWage(hourlyWage), hoursWorked(hoursWorked) {}

    void displaySalary() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Hourly Wage: $" << hourlyWage << "\n";
        cout << "Hours Worked: " << hoursWorked << "\n";
        cout << "Total Salary: $" << (hourlyWage * hoursWorked) << "\n\n";
    }
};

// Contractual Employee
class ContractualEmployee : public Employee {
private:
    double salaryPerProject;
    int numProjects;
public:
    ContractualEmployee(int id, string name, double salaryPerProject, int numProjects)
        : Employee(id, name), salaryPerProject(salaryPerProject), numProjects(numProjects) {}

    void displaySalary() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Contract Payment Per Project: $" << salaryPerProject << "\n";
        cout << "Projects Completed: " << numProjects << "\n";
        cout << "Total Salary: $" << (salaryPerProject * numProjects) << "\n\n";
    }
};

// Function to check for duplicate ID
bool isDuplicateID(int id, const vector<Employee*>& employees) {
    for (const auto& emp : employees) {
        if (emp->getId() == id) return true;
    }
    return false;
}

// Function to get a valid integer input
int getValidIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a positive number.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

// Function to get a valid floating-point input
double getValidDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a positive number.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

// Main menu function
void menu() {
    vector<Employee*> employees;
    int choice;

    while (true) {
        cout << "\nMenu\n";
        cout << "1 - Full-time Employee\n";
        cout << "2 - Part-time Employee\n";
        cout << "3 - Contractual Employee\n";
        cout << "4 - Display Payroll Report\n";
        cout << "5 - Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        if (choice == 5) break;

        int id = getValidIntInput("Enter Employee ID: ");
        while (isDuplicateID(id, employees)) {
            cout << "Duplicate ID! Enter a unique ID.\n";
            id = getValidIntInput("Enter Employee ID: ");
        }

        string name;
        cout << "Enter Employee Name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer before using getline
        getline(cin, name);

        switch (choice) {
            case 1: {
                double salary = getValidDoubleInput("Enter Fixed Salary: $");
                employees.push_back(new FullTimeEmployee(id, name, salary));
                break;
            }
            case 2: {
                double hourlyWage = getValidDoubleInput("Enter Hourly Wage: $");
                int hoursWorked = getValidIntInput("Enter Hours Worked: ");
                employees.push_back(new PartTimeEmployee(id, name, hourlyWage, hoursWorked));
                break;
            }
            case 3: {
                double salaryPerProject = getValidDoubleInput("Enter Payment Per Project: $");
                int numProjects = getValidIntInput("Enter Number of Projects: ");
                employees.push_back(new ContractualEmployee(id, name, salaryPerProject, numProjects));
                break;
            }
            case 4: {
                cout << "\n------ Employee Payroll Report ------\n";
                for (const auto& emp : employees) {
                    emp->displaySalary();
                }
                cout << "--------------------------------------\n\n";
                break;
            }
            default:
                cout << "Invalid choice! Try again.\n";
                break;
        }
    }

    // Free memory
    for (auto& emp : employees) {
        delete emp;
    }
}

// Main function
int main() {
    menu();
    return 0;
}