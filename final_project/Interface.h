#ifndef COSC_INTERFACE_H
#define COSC_INTERFACE_H

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <limits>
#include <fstream>
#include <sstream>
#include <regex>
#include "Grade.h"

namespace cosc1437_final{
    // convert string to lowercase to make input checks less tedious
    void to_lower(std::string&);

    // currently does not check for dupes nor does it check for sane scores
    void import_grades(const std::string&, std::vector<Grade>&);

    void export_grades(const std::string&, const std::vector<Grade>&);

    // DRY off user input checks
    // get_value may be ambiguous, so we'll specify that we want data from stdin
    template <typename T>
    T get_stdin_value();

    // simply gets the maximum possible score for the class from the user
    double get_max_course_score();

    // helper function for add_assignment and edit_assignment
    // collects and assigns data for constructing or editing Grades
    void collect_grade_data(std::string&, double&, double&);

    // add_assignment and edit_assignment are somewhat WET
    // but I really wanted to use emplace_back
    void add_assignment(std::vector<Grade>&);

    // simply adds up the scores
    double accumulate_score(const std::vector<Grade>&);

    // I'm normally not a fan of these kinds of functions but eh...
    // subtract earned_score from target_score; return zero if earned_score is greater
    double subtract_scores(double, double);

    // calculate scores needed to reach each letter grade
    // Note: we are assuming, for example, that a D is always 59.5.
    // This is not always the case.
    void calculate_earned_course_score(const std::vector<Grade>&, const double);

    // list assignments (and scores needed to reach each letter grade)
    void list_assignments(const std::vector<Grade>&);

    // edit assignment score (supposed to also edit comments but that doesn't work)
    void edit_grade(Grade&);

    // not const ref because we want to edit this
    void show_grade_details(std::vector<Grade>&, unsigned);

    // max_course_score is ref because we want to be able to OPTIONALLY edit it
    bool show_main_menu(std::vector<Grade>&, double&);
}

#endif
