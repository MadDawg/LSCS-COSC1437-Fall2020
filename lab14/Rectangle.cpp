#include "Rectangle.h"

Rectangle::Rectangle(){
    height_ = 0.0;
    width_ = 0.0;
}

Rectangle::Rectangle(double w, double h){
    height_ = h;
    width_ = w;
}

double Rectangle::perimeter() const{
    return 2*(width_ + height_);
}

double Rectangle::area() const{
    return width_ * height_;
}

double Rectangle::height() const{
    return height_;
}

double Rectangle::width() const{
    return width_;
}

void Rectangle::height(double h){
    height_ = h;
}

void Rectangle::width(double w){
    width_ = w;
}
