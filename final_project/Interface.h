#include "Grade.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <map>
#include <limits>
#include <sstream>
#include "Grade.h"

inline void to_lower(std::string& str){
    for (unsigned i = 0; i < str.size(); ++i){
        char& c = str[i];
        c = std::tolower(c);
    }
}

inline double calculate_score(const std::vector<Grade>& grades){
    double course_grade = 0.0;
    for (unsigned i = 0; i < grades.size(); i++){
        course_grade += grades[i].get_score();
    }
    return course_grade;
}

// I'm normally not a fan of these kinds of functions but eh...
inline double subtract_scores(double target_score, double earned_score){
    double score = target_score - earned_score;
    if (score < 0.0) return 0.0;
    return score;
}

inline void list_assignments(const std::vector<Grade>& grades){
    const double max_course_score = 2000.0;
    const std::map<char,double> course_scores = {
        {'A', 1790.0},
        {'B', 1590.0},
        {'C', 1390.0},
        {'D', 1190.0}
    };

    double earned_course_score = calculate_score(grades);

    std::cout << "+----+-------------------+-----+\n";
    // we should be using for_each here...
    for (unsigned i = 0; i < grades.size(); ++i){
        const Grade& grade = grades[i];
        std::cout << "| " << std::left << std::setw(3) << i+1 << "| "
            << std::setw(18) // length of "Abstraction Bonus" +1
            << grade.get_title() << "| " << std::setw(4)
            << grade.get_score() << "|\n"
            << "+----+-------------------+-----+\n";
    }

    std::cout << "Score needed to earn a perfect score: "
        << subtract_scores(max_course_score, earned_course_score) << '\n';

    for(auto iter = course_scores.begin(); iter != course_scores.end(); ++iter){
        std::string article = "a";
        if (iter->first == 'A'/* || iter->first == 'F'*/){ article = "an"; }
        std::cout << "Score needed to earn " << article << ' ' << iter->first << ' '
            << subtract_scores(iter->second, earned_course_score) << '\n';
    }
}

inline void edit_grade(Grade& grade){
    std::cout << "Editing " << grade.get_title() << ":\n";

    // TODO: validate input!
    std::cout << "Enter score: ";
    double score;

    while (true){
        std::cin >> score;
        if (!std::cin){
            std::cout << "Invalid input.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    if (score < 0){
        std::cout << "Entered score is too small; assigning zero.\n";
        grade.set_score(0.0);
    }
    else if (score > grade.get_max_score()){
        std::cout << "Entered score is too large; assigning perfect score.\n";
        grade.set_score(grade.get_max_score());
    }
    else{
        grade.set_score(score);
    }

    // B R O K E N! How does anyone do EOF stuff in C++?
    /*std::cout << "Enter comments (CTRL+D to finish): ";
    std::std::vector<std::string>& comments = grade.get_comments();

    while(!(std::cin >> std::ws).eof()){
        std::string comment;
        std::cin >> comment;
        if (std::cin.fail()){ break; } // just exit silently
        comments.push_back(comment);
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max());*/
}

// not const ref because we want to edit this
inline void show_grade_details(Grade& grade){
    while(true){
        std::cout << grade << '\n';
        std::cout << "(E)dit grade, (c)lear comments, or (r)eturn to main menu: ";
        std::string choice;

        while(true){
            std::cin >> choice;
            to_lower(choice);

            if (choice == "r"){
                return;
            }
            if (choice == "e"){
                edit_grade(grade);
                std::cout << "Grade updated.\n";
                break;
            }
            if (choice == "c"){
                grade.clear_comments();
                std::cout << "Comments cleared.\n";
                break;
            }
            std::cout << "Enter 'e', 'c', or 'r': ";
        }
    }
}

inline bool show_main_menu(std::vector<Grade>& grades){
    bool valid = false;
    while(!valid){
        std::cout << "\nSelect an assignment, or:\n"
            << "Fill (p)erfects, fill (z)eroes, (l)ist assignments, e(x)it: ";

        std::string choice;
        std::cin >> choice;
        to_lower(choice);
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // convert choice to integer
        // and check if it falls within the number of assignments
        try{
            int num_choice = stoi(choice);
            show_grade_details(grades[num_choice-1]);
        }
        catch(std::invalid_argument& e){
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
                std::cout << "Done.\n";
            }
            else if (choice == "z"){
                for (Grade& grade : grades){
                    grade.set_score(0.0);
                }
                std::cout << "Done.\n";
            }
            else if (choice == "q" || choice == "x"){
                std::cout << "Terminating.\n";
                return false;
            }
            else{
                std::cout << "Invalid input.\n";
            }
        }
    }
    return true;
}
