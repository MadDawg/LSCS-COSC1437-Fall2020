#include "Grade.h"

/*Grade::Grade(){
    score_ = 0.0;
    title_ = "";
}*/

// max_score is supposed to optional, therefore the ctor
// does not check if score is greater than max score
Grade::Grade(const std::string& title,
    const double score = 0.0,
    const double max_score = 100.0){

    max_score_ = max_score;
    set_score(score);
    set_title(title);
    // comments vector will just be initialized by its default constructor
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

std::vector<std::string>& Grade::get_comments(){
    return comments_;
}

// check if score is > max score
// and make appropriate correction
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
        << "\nComments: ";

    std::vector<std::string>& comments = grade.get_comments();

    if (comments.empty()){
        os << "none\n";
    }

    // will not execute if comments is empty
    for (unsigned i = 0; i < comments.size(); ++i){
        os << i+1 << ". " << comments[i] << '\n';
    }
    return os;
}
