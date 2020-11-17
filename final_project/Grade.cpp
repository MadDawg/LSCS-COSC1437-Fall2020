#include "Grade.h"

/*Grade::Grade(){
    score_ = 0.0;
    title_ = "";
}*/

// max_score is supposed to optional, therefore the ctor
// does not check if score is greater than max score
Grade::Grade(const std::string& title,
    const double score = 0.0,
    const double max_score = 100.0,
    const std::string& comments="none\n"){

    max_score_ = max_score;
    set_score(score);
    set_title(title);
    comments_ = comments;
}

double Grade::get_score() const{
    return score_;
}

void Grade::set_score(const double score){
    score_ = score;
}

double Grade::get_max_score() const{
    return max_score_;
}

void Grade::set_max_score(const double max_score){
    max_score_ = max_score;
}

std::string Grade::get_title() const{
    return title_;
}

void Grade::set_title(const std::string& title){
    title_ = title;
}

std::string Grade::get_comments() const{
    return comments_;
}

void Grade::add_comment(const std::string& comment){
    comments_ += comment;
}

// check if score is > max score
// and make appropriate correction
// this is still flimsy though (e.g. max_score_ < 0)
void Grade::sanitize(){
    if (score_ > max_score_){
        score_ = max_score_;
    }
}

void Grade::clear_comments(){
    comments_.clear();
}

std::ostream& operator<<(std::ostream& os, Grade& grade){
    os << "\nAssignment: " << grade.get_title()
        << "\nScore: " << grade.get_score()
        /*<< "\nComments: " << grade.get_comments()*/;

    // I really don't want to mess with the default ctor
    //if (grade.get_comments() == ""){ os << "none\n"; }
    return os;
}
