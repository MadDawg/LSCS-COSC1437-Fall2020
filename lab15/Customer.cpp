#include "Customer.h"

Customer::Customer(const std::string& fname, const std::string& lname,
    const std::string& email, const std::string& cust_number) : Person(fname, lname, email){
        customer_number = cust_number;
}

std::ostream& operator<<(std::ostream& os, const Customer& customer){
    return os << "Name: " << customer.full_name()
        << "\nEmail: " << customer.email_address
        << "\nNumber: " << customer.customer_number;
}
