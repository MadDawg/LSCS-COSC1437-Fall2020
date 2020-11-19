#ifndef COSC_GRADE_H
#define COSC_GRADE_H

#include <string>
#include <ostream>

class Grade{
private:
    double score_;
    double max_score_;
    std::string title_;
    std::string comments_;
public:
    Grade() = default;
    Grade(const std::string&, const double, const double, const std::string&);
    ~Grade() = default;

    // getter/setter pairs
    double get_score() const;
    void set_score(const double);

    double get_max_score() const;
    void set_max_score(const double);

    std::string get_title() const;
    void set_title(const std::string&);

    std::string get_comments() const;
    void add_comment(const std::string&);

    void sanitize();
    void clear_comments();

    friend std::ostream& operator<<(std::ostream&, Grade&);
};

#endif
