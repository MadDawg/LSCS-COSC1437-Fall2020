// Written by Cornell Washington

/*TODO:
* add TSV parser (import/export assignments)
*/

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

int main(){
    // extra credit is assumed to be a separate grade.
    vector<Grade> grades;
    /*vector<Grade> grades = {
        Grade("Week 1 Lab", 0.0, 100.0),
        Grade("Week 2 Lab", 0.0, 100.0),
        Grade("Chapter 1 Lab", 0.0, 100.0),
        Grade("Chapter 8 Lab", 0.0, 100.0),
        Grade("Chapter 10 Lab", 0.0, 100.0),
        Grade("Chapter 11 Lab", 0.0, 100.0),
        Grade("Chapter 12 Lab", 0.0, 100.0),
        Grade("Chapter 13 Lab", 0.0, 100.0),
        Grade("Chapter 14 Lab", 0.0, 100.0),
        Grade("Chapter 15 Lab", 0.0, 100.0),
        Grade("Chapter 16 Lab", 0.0, 100.0),
        Grade("Chapter 17 Lab", 0.0, 100.0),
        Grade("Abstraction Bonus", 0.0, 50.0),
        Grade("Final Project", 0.0, 300.0)
    };*/

    double max_course_score = get_max_course_score();
    list_assignments(grades);
    //calculate_earned_course_score(grades);

    bool keep_going = true;
    while(keep_going){
        keep_going = show_main_menu(grades, max_course_score);
    }
    return 0;
}
