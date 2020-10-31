#include "Person.h"

Person::Person(){
    first_name("");
    last_name("");
    email_address("");
}

Person::Person(const std::string& fname,
    const std::string& lname,
    const std::string& email){

    first_name(fname);
    last_name(lname);
    email_address(email);
}

std::string Person::full_name() const{
    return first_name_ + ' ' + last_name_;
}

// getters
std::string Person::first_name() const{
    return first_name_;
}

std::string Person::last_name() const{
    return last_name_;
}

std::string Person::email_address() const{
    return email_address_;
}

std::string Person::email() const{
    return email_address();
}

// setters
void Person::first_name(const std::string& fname){
    first_name_ = fname;
}

void Person::last_name(const std::string& lname){
    last_name_ = lname;
}

void Person::email_address(const std::string& email){
    email_address_ = email;
}

void Person::email(const std::string& email){
    email_address(email);
}
