// Written by Cornell Washington

// https://en.wikipedia.org/wiki/Virtual_inheritance
// https://en.cppreference.com/w/cpp/language/derived_class
// https://en.cppreference.com/w/cpp/language/virtual
// https://pencilprogrammer.com/cpp-tutorials/virtual-inheritance/
// https://www.cprogramming.com/tutorial/virtual_inheritance.html

#include <iostream>
#include <limits>
//#include <string> // included in Person.h
//#include "Person.h" // included in Customer.h and Employee.h
#include "Customer.h"
#include "Employee.h"
#include "Student.h"

using namespace std;

// a convenience function to DRY some things off
string get_value(const std::string& field){
    cout << field;
    string value;
    cin >> value;
    return value;
}

int main(){
    cout << "Customer/Employee Data Entry\n";

    while(true){
        cout << "\nCustomer, Employee, or Student? (c/e/s): ";
        char choice;

        while(true){
            cin >> choice;
            if(!cin){ // flaky
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.clear();
                choice = 0;
            }
            choice = tolower(choice);

            if (choice == 'c' || choice == 'e' || choice == 's'){
                break;
            }
            cout << "Please enter \'c\', \'e\', or \'s\': ";
        }

        string first_name = get_value("First name: ");
        string last_name = get_value("Last name: ");
        string email = get_value("Email: ");

        // one of these should be reachable
        if (choice == 'c'){
            string customer_number = get_value("Number: ");

            Customer customer(first_name, last_name, email, customer_number);
            cout << "\nCUSTOMER\n" << customer << '\n';
        }

        if (choice == 'e'){
            string ssn = get_value("SSN: ");

            Employee employee(first_name, last_name, email, ssn);
            cout << "\nEMPLOYEE\n" << employee << '\n';
        }

        if (choice == 's'){
            string customer_number = get_value("Customer Number: ");
            string sid = get_value("Student ID: ");
            string ssn = get_value("SSN: ");

            Student student(first_name, last_name, email, sid, customer_number, ssn);
            cout << "\nSTUDENT\n" << student << '\n';
        }

        cout << "\nContinue? (y/n): ";

        while(true){
            cin >> choice;
            if(!cin){
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.clear();
                choice = 0;
            }
            choice = tolower(choice);

            // else clauses unneeded due to break/return
            if (choice == 'y'){ break; }
            if (choice == 'n'){
                cout << "\nBye!\n";
                return 0; // We're done here. Exit program.
            }
            cout << "Please enter \'y\' or \'n\': ";
        }
    }
    return 0;
}
