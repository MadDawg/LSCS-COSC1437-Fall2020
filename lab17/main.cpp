// As of Aug 28, 2020, this will NOT compile under the versions of Clang and G++ (GCC)
// available on Repl.it. This will compile on GCC 8.3.0.

// Currently fails at the end of the while loop if the names are too long
// or too many names are entered.
// Failure modes are "free(): invalid pointer"
// or "munmap_chunk(): invalid pointer"

#include <iostream>
#include <string>
#include <memory>

// type alias
//using std::unique_ptr<std::unique_ptr<char[]>[]> = unique_2d_char;

typedef std::unique_ptr<std::unique_ptr<char[]>[]> unique_2d_char;
typedef std::shared_ptr<std::shared_ptr<char[]>[]> shared_2d_char;
typedef std::shared_ptr<std::unique_ptr<char[]>[]> shared_unique_2d_char;

void to_lower(std::string& str){
    for (int i = 0; i < str.size(); ++i){
        char& c = str[i];
        c = std::tolower(c);
    }
}

void swap_names(shared_unique_2d_char& names){
    names[0].swap(names[1]);
}

int main() {
    std::cout << "The Name Swapper\n\n";

    while(true){
        shared_2d_char names{new std::unique_ptr<char[]>[2]};
        names[0] = std::make_unique<char[]>(32);
        names[1] = std::make_unique<char[]>(32);

        std::cout << "Enter name 1: ";
        std::cin >> names[0].get();

        std::cout << "Enter name 2: ";
        std::cin >> names[1].get();

        std::cout << "Before swap\n"
        << "Name 1 is " << names[0] << '\n'
        << "Name 2 is " << names[1] << '\n';

        swap_names(names);

        std::cout << "After swap\n"
        << "Name 1 is " << names[0] << '\n'
        << "Name 2 is " << names[1] << '\n';

        std::cout << "Do you wish to continue? Type y or n: ";
        std::string choice;
        std::cin >> choice;
        to_lower(choice);
        while(true){
            if (choice == "y" || choice == "yes"){ break; }
            else if (choice == "n" || choice == "no"){
                std::cout << "Bye!\n";
                return 0;
            }
            else{
                std::cout << "Type y or n: ";
                std::cin >> choice;
            }
        }
    }
}

