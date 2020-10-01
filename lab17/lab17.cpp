#include <iostream>
#include <string>
//#include <cctype>
#include <algorithm>
//#include <limits>

using namespace std;

void to_lower(string& str){
  for (int i = 0; i < str.size(); ++i){
    char& c = str[i];
    c = tolower(c);
  }
}

void swap_names(char** names){
    char* temp = names[0];
    names[0] = names[1];
    names[1] = temp;
    //temp = nullptr; // just for thoroughness
}

int main() {
    const unsigned size = 256;

    cout << "The Name Swapper\n\n";
    while(true){
        char** names = new char*[2];
        names[0] = new char[size];
        names[1] = new char[size];

        cout << "Enter name 1: ";
        cin.getline(names[0], size, '\n');
        cout << "Enter name 2: ";
        cin.getline(names[1], size, '\n');

        cout << "Before swap\n"
        << "Name 1 is " << names[0] << '\n'
        << "Name 2 is " << names[1] << '\n';

        swap_names(names);

        cout << "After swap\n"
        << "Name 1 is " << names[0] << '\n'
        << "Name 2 is " << names[1] << '\n';

        // deallocate all arrays
        // we don't want any leaks
        delete[] names[0];
        delete[] names[1];
        delete[] names;

        cout << "Do you wish to continue? Type y or n: ";
        string choice;
        cin >> choice;
        cin.ignore();
        to_lower(choice);

        while(true){
            if (choice == "y" || choice == "yes"){ break; }
            else if (choice == "n" || choice == "no"){
                cout << "Bye!\n";
                return 0;
            }
            else{
                cout << "Type y or n: ";
                cin >> choice;
            }
        }
    }
}
