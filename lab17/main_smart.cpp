#include <iostream>
#include <string>
#include <memory>

using namespace std;

// type alias
typedef unique_ptr<unique_ptr<char[]>[]> unique_2d_char;

void to_lower(string& str){
    for (int i = 0; i < str.size(); ++i){
        char& c = str[i];
        c = tolower(c);
    }
}

// const ref to avoid violating uniqueness
void swap_names(const unique_2d_char& names){
    names[0].swap(names[1]); // mutates names even though it is marked const?
}

int main() {
    cout << "The Name Swapper\n\n";
    const unsigned size = 256;

    while(true){
        unique_2d_char names{new unique_ptr<char[]>[2]};
        names[0] = make_unique<char[]>(size);
        names[1] = make_unique<char[]>(size);

        cout << "Enter name 1: ";
        cin.getline(names[0].get(), size, '\n');

        cout << "Enter name 2: ";
        cin.getline(names[1].get(), size, '\n');

        cout << "Before swap\n"
        << "Name 1 is " << names[0].get() << '\n'
        << "Name 2 is " << names[1].get() << '\n';

        swap_names(names);

        cout << "After swap\n"
        << "Name 1 is " << names[0].get() << '\n'
        << "Name 2 is " << names[1].get() << '\n';

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
