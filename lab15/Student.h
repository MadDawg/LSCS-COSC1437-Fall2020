#ifndef STUDENT_H
#define STUDENT_H

#include "Customer.h"
#include "Employee.h"

// students get a discount at the university bookstore
// Employee may no longer be a meaningful typename
class Student : public Customer, public Employee{
private:
    std::string student_id_;
public:
    Student(const std::string& fname = "",
        const std::string& lname = "",
        const std::string& email = "",
        const std::string& sid = "",
        const std::string& cust_number = "",
        const std::string& ssn = ""){

        first_name(fname);
        last_name(lname);
        email_address(email);
        student_id(sid);
        customer_number(cust_number);
        social_security_number(ssn);
    }

    // getters
    const std::string student_id() const{
        return student_id_;
    }
    const std::string sid() const{
        return student_id();
    }

    // setters
    void student_id(const std::string& sid){
        student_id_ = sid;
    }
    void sid(const std::string& sid){ // function alias
        student_id(sid);
    }

    std::string to_string() const{
        return "Name: " + full_name()
            + "\nEmail: " + email_address()
            + "\nNumber: " + customer_number()
            + "\nStudent ID: " + student_id()
            + "\nSSN: " + social_security_number();
    }
};

// does not need to be a friend as to_string is public
std::ostream& operator<<(std::ostream& os, const Student& student){
    return os << student.to_string();
}

#endif
