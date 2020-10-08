// Written by Cornell Washington

#include <iostream>
#include <exception> // saves us some work
// #include <limits>

using namespace std;

double calculate_gross_pay(double hours, double payrate){
    double gross = 0.0;
    if (hours > 40){
        // hours - 40 gives the overtime hours
        // 40*payrate works because we know we worked at least 40 hours
        //gross = 1.5*(hours-40)*payrate + 40*payrate;
        gross = payrate*(1.5*(hours-40)+40);
    }
    else {
        gross = hours*payrate;
    }
    return gross;
}

int main(){
    cout << "Paycheck Calculator\n\n";
    bool badhours = false, badrate = false;
    double hours, rate;

    cout << "Hours worked: ";
    cin >> hours;
    if (cin.fail()){ badhours = true; }
    //cin.ignore(numeric_limits<streamsize>::max(), '\n'); // We don't need these for this particular assignment
    //cin.clear();

    cout << "Hourly rate of pay: ";
    cin >> rate;
    if (cin.fail()){ badrate = true; }
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //cin.clear();


    try{
        if (badhours){ throw invalid_argument("\nError! hours must be > 0.\n"); }
        else if (badrate){ throw invalid_argument("\nError! rate must be > 0.\n"); }
        else{
            cout << "Calculated gross pay: " << calculate_gross_pay(hours, rate) << '\n';
        }
    }
    catch(exception& e){
        cout << e.what();
    }

    cout << "\nBye!\n";
}
