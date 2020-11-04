#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <ostream>

class Rectangle{
private:
    double height_;
    double width_;
public:
    Rectangle();
    Rectangle(double, double);
    double perimeter() const;
    double area() const;

    // getters
    double height() const;
    double width() const;

    //setters
    void height(double);
    void width(double);

    //friend std::ostream& operator<<(std::ostream&, const Rectangle&);
};

std::ostream& operator<<(std::ostream&, const Rectangle&);

#endif
