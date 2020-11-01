#ifndef PERSON_H
#define PERSON_H

#include <ostream>
#include <string>

class Person{
private:
    std::string email_address_;
    std::string first_name_;
    std::string last_name_;
protected:
    // we do not want to just create an abstract Person
    // but we do want the ctor(s) to be inherited

    // we won't bother with pure virtual destructors here

    // default constructor is required in this case, default params are insufficient
    // see: https://stackoverflow.com/questions/36672027/no-matching-function-for-call-to-constructor
    Person();
    Person(const std::string&, const std::string&, const std::string&);
public:
    std::string full_name() const;
    std::string to_string() const;

    // getters
    std::string first_name() const;
    std::string last_name() const;
    std::string email_address() const;
    std::string email() const; // function alias

    //setters
    void first_name(const std::string&);
    void last_name(const std::string&);
    void email_address(const std::string&);
    void email(const std::string&); // function alias
};

std::ostream& operator<<(std::ostream&, const Person&);

#endif
