#include <iostream>
#include <map>
#include <string>

using namespace std;

char get_choice() {
	char choice;
	cout << "Continue (y/n)?:";
	cin >> choice;
	cout << endl;
	return choice;
}

void display_super_bowls(const map<string, string>& super_bowls) {
	cout << "Super Bowls: ";
	for (auto iterator = super_bowls.begin(); iterator != --super_bowls.end(); ++iterator){
    cout << iterator->first << ' ';
  }
  cout << (--super_bowls.end())->first;

	cout << endl << endl;
}

void display_winner(const map<string, string>& super_bowls) {
	string super_bowl;
	cout << "Enter a Super Bowl: ";
	cin >> super_bowl;
	string upper_super_bowl = "";
	for (char c : super_bowl) {
		upper_super_bowl += toupper(c);
	}

	// get iterator for map element with Super Bowl
  for (auto iterator = super_bowls.begin(); iterator != super_bowls.end(); iterator++){
    if (iterator->first == upper_super_bowl){
      // if the Super Bowl is found, display the winning team
      cout << "The winning team for Super Bowl " << iterator->first << ": " << iterator->second << "!\n";
      return;
    }
  }
  // if the Super Bowl isn't found, display a message
  cout << "Super Bowl " << upper_super_bowl << " not found.\n";
}

int main()
{
	map<string, string> super_bowls{
    {"I", "Packers"},
    {"II", "Packers"},
    {"III", "Jets"},
    {"IV", "Chiefs"},
    {"V", "Colts"},
    {"VI", "Cowboys"},
    {"VII", "Dolphins"},
    {"VIII", "Dolphins"},
    {"IX", "Dolphins"},
    {"X", "Steelers"},
    {"XI", "Raiders"},
    {"XII", "Cowboys"},
    {"XIII", "Steelers"},
    {"XIV", "Steelers"},
    {"XV", "Raiders"},
    {"XVI", "49ers"},
    {"XVII", "Redskins"},
    {"XVIII", "Raiders"},
    {"XIX", "49ers"},
    {"XX", "Bears"},
    {"XXI", "Giants"},
    {"XXII", "Redskins"},
    {"XXIII", "49ers"},
    {"XXIV", "49ers"},
    {"XXV", "Giants"},
    {"XXVI", "Redskins"},
    {"XXVII", "Cowboys"},
    {"XXVIII", "Cowboys"},
    {"XXIX", "49ers"},
    {"XXX", "Cowboys"},
    {"XXXI", "Packers"},
    {"XXXII", "Broncos"},
    {"XXXIII", "Broncos"},
    {"XXXIV", "Rams"},
    {"XXXV", "Ravens"},
    {"XXXVI", "Patriots"},
    {"XXXVII", "Buccaneers"},
    {"XXXVIII", "Patriots"},
    {"XXXIX", "Patriots"},
    {"XL", "Steelers"},
    {"XLI", "Colts"},
    {"XLII", "Giants"},
    {"XLIII", "Steelers"},
    {"XLIV", "Saints"},
    {"XLV", "Packers"},
    {"XLVI", "Giants"},
    {"XLVII", "Ravens"},
    {"XLVIII", "Seahawks"},
    {"XLIX", "Patriots"},
    {"50", "Broncos"},
    {"LI", "Patriots"},
    {"LII", "Eagles"},
    {"LIII", "Patriots"},
    {"LIV", "Chiefs"},
  };

	cout << "The Super Bowls Program\n\n";

	// display the Super Bowls
  display_super_bowls(super_bowls);

	// while the user indicates they want to continue, display a winner
  while(true){
    display_winner(super_bowls);
    while(true){
      char choice = tolower(get_choice()); // Get choice, converted to lower case
      if (choice == 'n'){ return 0; } // Done. End program.
      else if (choice == 'y'){ break; } // Escape choice loop
      else{ cout << "Invalid input.\n"; } // Do nothing other than print. Loop will continue.
    }
  }
}
