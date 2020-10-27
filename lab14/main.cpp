// Written by Cornell Washington

#include <iostream>
#include <cctype>
#include "Rectangle.h"

using namespace std;

int main(){
    cout << "Rectangle Calculator\n";
    while(true){
        double height, width;

        cout << "\nHeight: ";
        cin >> height;

        cout << "Width: ";
        cin >> width;

        // construct rectangle using width and height
        // default constructor and getter/setters are unused
        Rectangle rect(width, height);
        cout << "Perimeter: " << rect.perimeter()
            << "\nArea: " << rect.area();

        cout << "\n\nContinue? (y/n): ";
        char choice;

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
}
