#include "Person.h"

Person::Person(const std::string& fname, const std::string& lname, const std::string& email){
    first_name = fname;
    last_name = lname;
    email_address = email;
}

std::string Person::full_name() const{
    return first_name + ' ' + last_name;
}
