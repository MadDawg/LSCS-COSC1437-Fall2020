// Written by Cornell Washington

/*
* [...] you may develop your own interface,
* but it must provide the minimum functionality demonstrated.
* https://codeboard.io/projects/189532
*/

// We are definitely developing our own interface here.

// None of these seem to work...
// https://stackoverflow.com/questions/5605125/why-is-iostreameof-inside-a-loop-condition-i-e-while-stream-eof-cons
// https://stackoverflow.com/questions/4939251/cin-eof-functionality
// https://stackoverflow.com/questions/28633195/cannot-cin-ignore-till-eof
// https://stackoverflow.com/questions/201992/how-to-read-until-eof-from-cin-in-c

// "grade" and "assignment" are effectively synonymous

#include "Interface.h"

using namespace std;
using namespace cosc1437_final;

int main(){
    vector<Grade> grades;

    double max_course_score = get_max_course_score();
    list_assignments(grades);

    // will loop so long as show_main_menu returns true
    while(show_main_menu(grades, max_course_score));
    return 0;
}
