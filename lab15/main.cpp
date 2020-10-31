// Written by Cornell Washington

#include <iostream>
//#include "Person.h" // included in Customer.h and Employee.h
#include "Customer.h"
#include "Employee.h"
// #include <string> // included in Person.h

using namespace std;

/*bool ask_repeat(const char* question = "Continue?", const char* choices = "yn"){
    // assumes we only have 2 choices
    cout << "\n\n"
        << question
        << '(' << choices[0] << '/' << choices[1] << "): ";
    char choice;

    while(true){
        cin >> choice;
        choice = tolower(choice);

        // else clauses unneeded due to break/return
        if (choice == 'y'){ return true; }
        if (choice == 'n'){
            //cout << "\nBye!\n";
            return false; // We're done here. Exit program.
        }
        cout << "Please enter \'" << choices[0]
            << "\' or \'" << choices[1] << "\': ";
    }
}*/


int main(){
    cout << "Customer/Employee Data Entry\n";

    while(true){
        cout << "\nCustomer or Employee? (c/e): ";
        char choice;

        while(true){
            cin >> choice;
            choice = tolower(choice);

            if (choice == 'c' || choice == 'e'){
                break;
            }
            cout << "Please enter \'c\' or \'e\': ";
        }

        std::string first_name, last_name, email;

        cout << "First name: ";
        cin >> first_name;

        cout << "Last name: ";
        cin >> last_name;

        cout << "Email: ";
        cin >> email;

        // one of these should be reachable
        if (choice == 'c'){
            cout << "Number: ";
            std::string customer_number;
            cin >> customer_number;

            Customer customer(first_name, last_name, email, customer_number);
            cout << "\nCUSTOMER\n" << customer << '\n';
        }

        if (choice == 'e'){
            cout << "SSN: ";
            std::string ssn;
            cin >> ssn;

            Employee employee(first_name, last_name, email, ssn);
            cout << "\nEMPLOYEE\n" << employee << '\n';
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
