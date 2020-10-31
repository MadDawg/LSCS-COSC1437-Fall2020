#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <ostream>
#include "Person.h"

class Employee : public Person{
private:
    std::string social_security_number;
public:
    Employee(const std::string&, const std::string&, const std::string&, const std::string&);
    friend std::ostream& operator<<(std::ostream&, const Employee&);
};

#endif
