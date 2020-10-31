#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"

class Customer : virtual public Person{
private:
    std::string customer_number_;
public:
    Customer(const std::string& fname = "",
        const std::string& lname = "",
        const std::string& email = "",
        const std::string& cust_number = "") : Person(fname, lname, email){

        customer_number(cust_number);
    }

    // getter/setter pair
    std::string customer_number() const{
        return customer_number_;
    }

    void customer_number(const std::string& cust_number){
        customer_number_ = cust_number;
    }

    std::string to_string() const{
        return "Name: " + full_name()
            + "\nEmail: " + email_address()
            + "\nNumber: " + customer_number();
    }
};

// does not need to be a friend as to_string is public
std::ostream& operator<<(std::ostream& os, const Customer& customer){
    return os << customer.to_string();
}


#endif
