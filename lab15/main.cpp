// Written by Cornell Washington

// https://en.wikipedia.org/wiki/Virtual_inheritance
// https://pencilprogrammer.com/cpp-tutorials/virtual-inheritance/
// https://www.cprogramming.com/tutorial/virtual_inheritance.html

#include <iostream>
//#include "Person.h" // included in Customer.h and Employee.h
#include "Customer.h"
#include "Employee.h"
#include "Student.h"
// #include <string> // included in Person.h

using namespace std;

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
            choice = tolower(choice);

            if (choice == 'c' || choice == 'e' || choice == 's'){
                break;
            }
            cout << "Please enter \'c\', \'e\', or \'s\': ";
        }

        string first_name, last_name, email;

        cout << "First name: ";
        cin >> first_name;

        cout << "Last name: ";
        cin >> last_name;

        cout << "Email: ";
        cin >> email;

        // one of these should be reachable
        if (choice == 'c'){
            cout << "Number: ";
            string customer_number;
            cin >> customer_number;

            Customer customer(first_name, last_name, email, customer_number);
            cout << "\nCUSTOMER\n" << customer << '\n';
        }

        if (choice == 'e'){
            cout << "SSN: ";
            string ssn;
            cin >> ssn;

            Employee employee(first_name, last_name, email, ssn);
            cout << "\nEMPLOYEE\n" << employee << '\n';
        }

        if (choice == 's'){
            string customer_number = get_value("Number: ");
            string sid = get_value("Student ID: ");
            string ssn = get_value("SSN: ");

            Student student(first_name, last_name, email, sid, customer_number, ssn);
            cout << "\nStudent\n" << student << '\n';

        }

        cout << "\nContinue? (y/n): ";

        while(true){
            cin >> choice;
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
