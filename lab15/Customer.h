#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <ostream>
#include "Person.h"

class Customer : public Person{
private:
    std::string customer_number;
public:
    Customer(const std::string&, const std::string&, const std::string&, const std::string&);
    friend std::ostream& operator<<(std::ostream&, const Customer&);
};

#endif
