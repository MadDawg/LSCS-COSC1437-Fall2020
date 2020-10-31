#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person{
// friend functions of derived classes
// cannot access private members (haha) of descendants
protected:
    std::string email_address;
    std::string first_name;
    std::string last_name;
protected:
    // we do not want to just create an abstract Person
    // but we do want the ctor(s) to be inherited
    //Person();
    Person(const std::string&, const std::string&, const std::string&);
public:
    std::string full_name() const;
    //friend std::ostream& operator<<(std::ostream&, const Person&);
};

#endif
