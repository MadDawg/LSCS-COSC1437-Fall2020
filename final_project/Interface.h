#ifndef COSC_INTERFACE_H
#define COSC_INTERFACE_H

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <map>
#include <limits>
#include <fstream>
#include <sstream>
#include <regex>
#include "Grade.h"

// convert string to lowercase to make input checks less tedious
inline void to_lower(std::string& str){
    for (unsigned i = 0; i < str.size(); ++i){
        char& c = str[i];
        c = std::tolower(c);
    }
}

// currently does not check for dupes nor does it check for sane scores
inline void import_grades(const std::string& filename, std::vector<Grade>& grades){
    std::ifstream ifs(filename);
    if (!ifs){
        std::cout << "Could not open file \"" << filename << "\".\n"
            << "Make sure file exists and is readable\n";
    }
    int i = 0;
    while(ifs){
        // using regex here saves us a lot of input checking

        //std::regex expression("^(.+)\\t(\\d+|\\d+\\.\\d+)\\t(\\d+|\\d+\\.\\d+)$");

        // Expression matches beginning of the line
        // plus any character up to a tab character
        // plus one+ digits or one+ digits plus a dot and another one+ digits
        // followed by a tab character
        // plus one+ digits or one+ digits plus a dot and another one+ digits
        // followed by a tab character

        // EOL match ('$') does not seem to work.
        // This looks to be an issue with the compiler
        // (both GCC 9.3.0 and Clang7) itself.
        // https://stackoverflow.com/questions/61195222/stdregexmultiline-does-not-exist
        // Viewing the header files confirms this.
        // Note that the multiline feature may not actually help solve the EOL issue.

        // This expression is good enough;
        // it will just silently ignore extra trailing data
        std::regex expression(R"(^(.+)\t(\d+|\d+\.\d+)\t(\d+|\d+\.\d+))");
        std::smatch matches;
        std::string line;

        std::getline(ifs, line);

        if(std::regex_search(line, matches, expression)){
            std::string title = matches[1].str();
            double max_score = std::stod(matches[2].str());
            double score = std::stod(matches[3].str());
            grades.emplace_back(title, score, max_score, "none\n");
            ++i;
        }
    }
    std::cout << i << " assignments imported.\n";
}

inline void export_grades(const std::string& filename, const std::vector<Grade>& grades){
    // we want to overwrite the file,
    // but we also want to be sure we get every assignment
    std::ofstream ofs(filename);
    std::stringstream ss;
    for (const Grade& grade : grades){
        ss << grade.get_title() << '\t' << grade.get_max_score()
            << '\t' << grade.get_score() << '\n';
    }
    ofs << ss.str();
    try{
        ofs.exceptions(ofs.failbit);
    }
    catch(const std::ios_base::failure& e){
        // message does not cover every failure mode, but mentioning permissions
        // should be sufficient in directing the user toward the solution
        std::cout << "Could not write to file \"" << filename << "\".\n"
            << "Make sure directory exists and is writable.\n";
    }

}

// DRY off user input checks
// get_value may be ambiguous, so we'll specify that we want data from stdin
template <typename T>
inline T get_stdin_value(){
    T value;
    while (true){
        std::cin >> value;
        if (!std::cin){
            std::cout << "Invalid input. Try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

// simply gets the maximum possible score for the class from the user
inline double get_max_course_score(){
    std::cout << "Enter the maximum score that can be earned in the course: ";
    double max_course_score;

    while (true){
        max_course_score = get_stdin_value<double>();
        if (max_course_score < 0.0){
            std::cout << "Score must be zero or greater. Try again: ";
        }
        else{ return max_course_score; }
    }
}

// helper function for add_assignment and edit_assignment
// collects and assigns data for constructing or editing Grades
inline void collect_grade_data(std::string& name, double& max_score, double& score){
    std::cout << "Enter new assignment name: ";
    //name = get_stdin_value<std::string>();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, name);

    std::cout << "Enter maximum possible score for assignment: ";
    max_score = get_stdin_value<double>();

    std::cout << "Enter score earned on assignment: ";
    score = get_stdin_value<double>();
    while(score > max_score){
        std::cout << "Earned score is greater than maximum score. "
            << "Try again: ";
        score = get_stdin_value<double>();
    }

}

// add_assignment and edit_assignment are somewhat WET
// but I really wanted to use emplace_back
inline void add_assignment(std::vector<Grade>& grades){
    std::string name;
    double max_score, score;
    collect_grade_data(name, max_score, score);
    grades.emplace_back(name, score, max_score, "none\n");
}

// simply adds up the scores
inline double accumulate_score(const std::vector<Grade>& grades){
    double course_grade = 0.0;
    for (const Grade& grade : grades){
        course_grade += grade.get_score();
    }
    return course_grade;
}

// I'm normally not a fan of these kinds of functions but eh...
// subtract earned_score from target_score; return zero if earned_score is greater
inline double subtract_scores(double target_score, double earned_score){
    double score = target_score - earned_score;
    if (score < 0.0) return 0.0;
    return score;
}

// calculate scores needed to reach each letter grade
// Note: we are assuming, for example, that a D is always 59.5.
// This is not always the case.
inline void calculate_earned_course_score(const std::vector<Grade>& grades, const double max_course_score){
    const std::map<char,double> course_scores = {
        {'A', max_course_score*0.895},
        {'B', max_course_score*0.795},
        {'C', max_course_score*0.695},
        {'D', max_course_score*0.595}
    };

    double earned_course_score = accumulate_score(grades);

    std::cout << "Max possible score: " << max_course_score << '\n'
        << "Score earned: " << earned_course_score << '\n';

    std::cout << "Score needed to earn a perfect score: "
        << subtract_scores(max_course_score, earned_course_score) << '\n';

    for(auto iter = course_scores.begin(); iter != course_scores.end(); ++iter){
        std::string article = "a"; // grammar
        if (iter->first == 'A'){ article = "an"; }
        std::cout << "Score needed to earn " << article << ' ' << iter->first << ' '
            << subtract_scores(iter->second, earned_course_score) << '\n';
    }
}

// list assignments (and scores needed to reach each letter grade)
inline void list_assignments(const std::vector<Grade>& grades){
    if (grades.empty()){
        std::cout << "There are currently no assignments to list.\n";
        return;
    }

    // somewhat WET but this is acceptable
    std::cout << "+----+-------------------+-------+\n";
    std::cout << "| " << std::left << std::setw(3) << '#' << "| "
        << std::setw(18) << "Assignment" << "| " << std::setw(6)
        << "Score" << "|\n"
        << "+----+-------------------+-------+\n";

    for (unsigned i = 0; i < grades.size(); ++i){
        const Grade& grade = grades[i];
        std::cout << "| " << std::left << std::setw(3) << i+1 << "| "
            << std::setw(18) // length of "Abstraction Bonus" +1
            << grade.get_title() << "| " << std::setw(6)
            << grade.get_score() << "|\n"
            << "+----+-------------------+-------+\n";
    }
}

// edit assignment score (supposed to also edit comments but that doesn't work)
inline void edit_grade(Grade& grade){
    std::cout << "Editing \"" << grade.get_title() << "\"...\n";

    std::string name;
    double max_score, score;
    collect_grade_data(name, max_score, score);

    grade.set_score(score);

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
inline void show_grade_details(std::vector<Grade>& grades, unsigned index){
    Grade& grade = grades[index];
    while(true){
        std::cout << grade << '\n';
        std::cout << "What would you like to do?\n"
            << "- e: Edit assignment\n"
            //<< "- c: Clear comments\n"
            << "- d: Remove assignment\n"
            << "- r: Return to main menu\n"
            << "Enter choice:  ";
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
            /*if (choice == "c"){
                grade.clear_comments();
                std::cout << "Comments cleared.\n";
                break;
            }*/
            // TODO: ask for confirmation
            if (choice == "d"){
                auto it = grades.begin();
                std::cout << "Removing \"" << grade.get_title() << "\"...\n";
                grades.erase(it+index);
                std::cout << "Done.\n";
                return;
            }
            //std::cout << "Enter 'e', 'c', 'd', or 'r': ";
            std::cout << "Enter 'e', 'd', or 'r': ";
        }
    }
}

// max_course_score is ref because we want to be able to OPTIONALLY edit it
inline bool show_main_menu(std::vector<Grade>& grades, double& max_course_score){
    bool valid = false;
    while(!valid){
        std::cout << "What would you like to do?\n";
        if (grades.size() > 1){
            std::cout << "\n- 1-" << grades.size() << ": Select an assignment from the list\n";
        }
        else if (grades.size() == 1){
            std::cout << "\n- 1: Select assignment\n";
        }
        std::cout << "- l: List assignments\n"
            << "- m: Edit maximum course score\n"
            << "- g: Show course score information\n"
            << "- a: Add assignment\n"
            << "- d: Remove assignment\n"
            << "- i: Import assignments\n"
            << "- e: Export assignments\n"
            << "- p: Fill perfects\n"
            << "- z: Fill zeroes\n"
            << "- x: Exit\n"
            << "Enter choice: ";

        std::string choice;
        std::cin >> choice;
        to_lower(choice);
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // convert choice to integer
        // and check if it falls within the number of assignments
        try{
            // stoi throws invalid_argument if conversion fails
            int num_choice = std::stoi(choice);
            // assignment chosen (if it exists)
            if (static_cast<unsigned>(num_choice) > grades.size() || num_choice < 1){
                std::cout << "Assignment " << num_choice << " does not exist.\n";
                return true;
            }
            // implicit cast to unsigned
            show_grade_details(grades, num_choice-1);
        }
        catch(std::invalid_argument& e){
            if (choice == "l"){
                list_assignments(grades);
                //calculate_earned_course_score(grades);
            }
            else if (choice == "m"){
                max_course_score = get_max_course_score();
            }
            else if (choice == "g"){
                calculate_earned_course_score(grades, max_course_score);
            }
            else if (choice == "a"){
                add_assignment(grades);
            }
            // TODO: ask for confirmation
            else if (choice == "d"){
                if (!grades.empty()){
                    if (grades.size() == 1){
                        grades.clear();
                        std::cout << "Assignment removed.\n";
                        return true;
                    }
                    std::cout << "Choose an assignment to remove "
                        << "1-" << grades.size() << ", 'a' for all, or 'c' to cancel: ";

                    while(true){
                        // we can reuse this
                        choice = get_stdin_value<std::string>();
                        try{
                            // reusing this also
                            int num_choice = std::stoi(choice);
                            if (static_cast<unsigned>(num_choice) > grades.size() || num_choice < 1){
                                std::cout << "Assignment " << num_choice << " does not exist.\n";
                                return true;
                            }
                            auto iter = grades.begin();
                            std::cout << "Removing \""
                                << (iter+num_choice-1)->get_title() << "\"...\n";

                            grades.erase(iter+num_choice-1);
                            std::cout << "Done.\n";
                            return true;
                        }
                        catch(std::invalid_argument& err){
                            if(choice == "a"){
                                grades.clear();
                                std::cout << "All assignments removed.\n";
                                return true;
                            }
                            else if (choice == "c" || choice == "n"){
                                std::cout << "No assignments removed.\n";
                                return true;
                            }
                            std::cout << "Invalid input. Try again: ";
                        }
                    }
                }
                std::cout << "There are no assignments to remove.\n";

            }
            else if (choice == "i"){
                std::cout << "Enter filename: ";
                std::string filename;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, filename);
                import_grades(filename, grades);
            }
            else if(choice == "e"){
                if (grades.empty()){
                    std::cout << "There are no assignments to export.\n";
                    return true;
                }
                std::cout << "Enter filename: ";
                std::string filename;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, filename);
                export_grades(filename, grades);
            }
            else if (choice == "p"){ // fill with perfect scores
                if (grades.empty()){
                    std::cout << "There are no grades to edit.\n";
                    return true;
                }
                for (Grade& grade : grades){
                    grade.set_score(grade.get_max_score());
                }
                std::cout << "Done.\n";
            }
            else if (choice == "z"){ // fill with zeroes
                if (grades.empty()){
                    std::cout << "There are no grades to edit.\n";
                    return true;
                }
                for (Grade& grade : grades){
                    grade.set_score(0.0);
                }
                std::cout << "Done.\n";
            }
            else if (choice == "q" || choice == "x"){ // exit program
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

#endif
