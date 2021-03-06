#ifndef RECTANGLE_H
#define RECTANGLE_H

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
};

#endif
