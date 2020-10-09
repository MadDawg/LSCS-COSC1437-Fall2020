// Written by Cornell Washington

#include <iostream>
#include <exception> // saves us some work

using namespace std;

double calculate_gross_pay(double hours, double payrate){

    if (hours <= 0){ throw invalid_argument("\nError! hours must be > 0.\n"); }
    else if (payrate <= 0){ throw invalid_argument("\nError! rate must be > 0.\n"); }

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

    double hours, rate;

    cout << "Hours worked: ";
    cin >> hours;

    cout << "Hourly rate of pay: ";
    cin >> rate;

    try{
        double gross_pay = calculate_gross_pay(hours, rate);
        cout << "Calculated gross pay: " << gross_pay << '\n';
    }
    catch(exception& e){
        cout << e.what();
    }

    cout << "\nBye!\n";
}
