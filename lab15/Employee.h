#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Person.h"

class Employee : virtual public Person{
private:
    std::string social_security_number_;
public:
    Employee(const std::string& fname = "",
        const std::string& lname = "",
        const std::string& email = "",
        const std::string& ssn = "") : Person(fname, lname, email){

        social_security_number(ssn);
    }

    // getters
    std::string social_security_number() const{
        return social_security_number_;
    }
    std::string ssn() const{ // function alias
        return social_security_number();
    }

    // setters
    void social_security_number(const std::string& ssn){
        social_security_number_ = ssn;
    }
    void ssn(const std::string& ssn){ //function alias
        social_security_number(ssn);
    }

    std::string to_string() const{
        return "Name: " + full_name()
            + "\nEmail: " + email_address()
            + "\nSSN: " + social_security_number();
    }
};

// does not need to be a friend as to_string is public
std::ostream& operator<<(std::ostream& os, const Employee& employee){
    return os << employee.to_string();
}


#endif
