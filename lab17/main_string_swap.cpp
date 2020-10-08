#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void to_lower(string& str){
    for (int i = 0; i < str.size(); ++i){
        char& c = str[i];
        c = tolower(c);
    }
}

void swap_names(string& name1, string& name2){
    name1.swap(name2);
}

// lol
void swap_names(string* name1, string* name2){
    (*name1).swap(*name2);
}

int main() {
    cout << "The Name Swapper\n\n";

    while(true){
        string name1, name2;

        cout << "Enter name 1: ";
        getline(cin, name1);

        cout << "Enter name 2: ";
        getline(cin, name2);

        cout << "Before swap\n"
        << "Name 1 is " << name1 << '\n'
        << "Name 2 is " << name2 << '\n';

        // I'd prefer to do it this way, but you know how it is...
        // swap_names(name1, name2);

        swap_names(&name1, &name2);

        cout << "After swap\n"
        << "Name 1 is " << name1 << '\n'
        << "Name 2 is " << name2 << '\n';

        cout << "Do you wish to continue? Type y or n: ";
        string choice;
        cin >> choice;
        while(true){
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            to_lower(choice);
            if (choice == "y" || choice == "yes"){
                break;
            }
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
