// Written by Cornell Washington

/*
* This is a working model of the program.
* Your program may replicate this example.
* Or, you may develop your own interface,
* but it must provide the minimum functionality demonstrated.
* https://codeboard.io/projects/189532
*/

// None of these seem to work...
// https://stackoverflow.com/questions/5605125/why-is-iostreameof-inside-a-loop-condition-i-e-while-stream-eof-cons
// https://stackoverflow.com/questions/4939251/cin-eof-functionality
// https://stackoverflow.com/questions/28633195/cannot-cin-ignore-till-eof
// https://stackoverflow.com/questions/201992/how-to-read-until-eof-from-cin-in-c

// We are definitely developing our own interface here.
// There is no need to manually type assignment names.

// "grade" and "assignment" are effectively synonymous

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <map>
#include <limits>
#include <sstream>
#include "Grade.h"

using namespace std;

void to_lower(string& str){
    for (unsigned i = 0; i < str.size(); ++i){
        char& c = str[i];
        c = tolower(c);
    }
}

double calculate_score(const vector<Grade>& grades){
    double course_grade = 0.0;
    for (unsigned i = 0; i < grades.size(); i++){
        course_grade += grades[i].get_score();
    }
    return course_grade;
}

// I'm normally not a fan of these kinds of functions but eh...
double subtract_scores(double target_score, double earned_score){
    double score = target_score - earned_score;
    if (score < 0.0) return 0.0;
    return score;
}

void list_assignments(const vector<Grade>& grades){
    const double max_course_score = 2000.0;
    const map<char,double> course_scores = {
        {'A', 1790.0},
        {'B', 1590.0},
        {'C', 1390.0},
        {'D', 1190.0}
    };

    double earned_course_score = calculate_score(grades);

    cout << "+----+-------------------+-----+\n";
    // we should be using for_each here...
    for (unsigned i = 0; i < grades.size(); ++i){
        const Grade& grade = grades[i];
        cout << "| " << left << setw(3) << i+1 << "| "
            << setw(18) // length of "Abstraction Bonus" +1
            << grade.get_title() << "| " << setw(4)
            << grade.get_score() << "|\n"
            << "+----+-------------------+-----+\n";
    }

    cout << "Score needed to earn a perfect score: "
        << subtract_scores(max_course_score, earned_course_score) << '\n';

    for(auto iter = course_scores.begin(); iter != course_scores.end(); ++iter){
        string article = "a";
        if (iter->first == 'A'/* || iter->first == 'F'*/){ article = "an"; }
        cout << "Score needed to earn " << article << ' ' << iter->first << ' '
            << subtract_scores(iter->second, earned_course_score) << '\n';
    }
}

void edit_grade(Grade& grade){
    cout << "Editing " << grade.get_title() << ":\n";

    // TODO: validate input!
    cout << "Enter score: ";
    double score;

    while (true){
        cin >> score;
        if (!cin){
            cout << "Invalid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            //cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    if (score < 0){
        cout << "Entered score is too small; assigning zero.\n";
        grade.set_score(0.0);
    }
    else if (score > grade.get_max_score()){
        cout << "Entered score is too large; assigning perfect score.\n";
        grade.set_score(grade.get_max_score());
    }
    else{
        grade.set_score(score);
    }

    // B R O K E N! How does anyone do EOF stuff in C++?
    /*cout << "Enter comments (CTRL+D to finish): ";
    vector<string>& comments = grade.get_comments();

    while(!(cin >> std::ws).eof()){
        string comment;
        cin >> comment;
        if (cin.fail()){ break; } // just exit silently
        comments.push_back(comment);
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max());*/
}

// not const ref because we want to edit this
void show_grade_details(Grade& grade){
    while(true){
        cout << grade << '\n';
        cout << "(E)dit grade, (c)lear comments, or (r)eturn to main menu: ";
        string choice;

        while(true){
            cin >> choice;
            to_lower(choice);

            if (choice == "r"){
                return;
            }
            if (choice == "e"){
                edit_grade(grade);
                cout << "Grade updated.\n";
                break;
            }
            if (choice == "c"){
                grade.clear_comments();
                cout << "Comments cleared.\n";
                break;
            }
            cout << "Enter 'e', 'c', or 'r': ";
        }
    }
}

bool show_main_menu(vector<Grade>& grades){
    bool valid = false;
    while(!valid){
        cout << "\nSelect an assignment, or:\n"
            << "Fill (p)erfects, fill (z)eroes, (l)ist assignments, e(x)it: ";

        string choice;
        cin >> choice;
        to_lower(choice);
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // convert choice to integer
        // and check if it falls within the number of assignments
        try{
            int num_choice = stoi(choice);
            show_grade_details(grades[num_choice-1]);
        }
        catch(invalid_argument& e){
            if (choice == "l"){ list_assignments(grades); }
            else if (choice == "p"){
                for (Grade& grade : grades){
                    if (grade.get_title() == "Abstraction Bonus"){
                        grade.set_score(50.0);
                    }
                    else if (grade.get_title() == "Final Project"){
                        grade.set_score(300.0);
                    }
                    else { grade.set_score(100.0); }
                }
                cout << "Done.\n";
            }
            else if (choice == "z"){
                for (Grade& grade : grades){
                    grade.set_score(0.0);
                }
                cout << "Done.\n";
            }
            else if (choice == "q" || choice == "x"){
                cout << "Terminating.\n";
                return false;
            }
            else{
                cout << "Invalid input.\n";
            }
        }
    }
    return true;
}

int main(){
    // extra credit is assumed to be a seperate grade.
    vector<Grade> grades = {
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
    };

    list_assignments(grades); // may have the user control this (after the first call)

    bool keep_going = true;
    while(keep_going){
        keep_going = show_main_menu(grades);
    }

    return 0;
}
