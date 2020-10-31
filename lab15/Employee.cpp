#include "Employee.h"

Employee::Employee(const std::string& fname, const std::string& lname,
    const std::string& email, const std::string& ssn) : Person(fname, lname, email){
        social_security_number = ssn;
}

std::ostream& operator<<(std::ostream& os, const Employee& employee){
    return os << "Name: " << employee.full_name()
        << "\nEmail: " << employee.email_address
        << "\nSSN: " << employee.social_security_number;
}
