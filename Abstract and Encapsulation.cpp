#include <iostream>
#include <vector>
#include <string>
#include <limits> 

using namespace std;

class Employee {
protected:
    int id;
    string name;
public:
    Employee(int id, string name) : id(id), name(name) {}
    virtual void displaySalary() const = 0; 
    int getId() const { return id; }
    virtual ~Employee() {}
};

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

bool isDuplicateID(int id, const vector<Employee*>& employees) {
    for (const auto& emp : employees) {
        if (emp->getId() == id) return true;
    }
    return false;
}

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
            return value;
        }
    }
}

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
            return value;
        }
    }
}

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

        switch (choice) {
            case 1: {
                int id = getValidIntInput("Enter Employee ID: ");
                while (isDuplicateID(id, employees)) {
                    cout << "Duplicate ID! Enter a unique ID.\n";
                    id = getValidIntInput("Enter Employee ID: ");
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Employee Name: ";
                string name;
                getline(cin, name);

                double salary = getValidDoubleInput("Enter Fixed Salary: $");
                employees.push_back(new FullTimeEmployee(id, name, salary));
                break;
            }
            case 2: {
                int id = getValidIntInput("Enter Employee ID: ");
                while (isDuplicateID(id, employees)) {
                    cout << "Duplicate ID! Enter a unique ID.\n";
                    id = getValidIntInput("Enter Employee ID: ");
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Employee Name: ";
                string name;
                getline(cin, name);

                double hourlyWage = getValidDoubleInput("Enter Hourly Wage: $");
                int hoursWorked = getValidIntInput("Enter Hours Worked: ");
                employees.push_back(new PartTimeEmployee(id, name, hourlyWage, hoursWorked));
                break;
            }
            case 3: {
                int id = getValidIntInput("Enter Employee ID: ");
                while (isDuplicateID(id, employees)) {
                    cout << "Duplicate ID! Enter a unique ID.\n";
                    id = getValidIntInput("Enter Employee ID: ");
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Employee Name: ";
                string name;
                getline(cin, name);

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
                break;
            }
            default:
                cout << "Invalid choice! Try again.\n";
                break;
        }
    }

    for (auto& emp : employees) {
        delete emp;
    }
}

int main() {
    menu();
    return 0;
}
