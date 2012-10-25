// circle.h

#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include "base_ellipse.h"

using std::cout;
using std::endl;

class Circle: public BaseEllipse
{
public:
    Circle(double x0=0, double y0=0, double r0 = 0);
    ~Circle();
    virtual double Area() const;
    virtual void showValue() const;
    
private:
    double r;       //radius
};

Circle::Circle(double x0, double y0, double r0): BaseEllipse(x0, y0)
{
    r = r0;
    cout << "Circle::Circle()" << endl;
}

Circle::~Circle()
{
    cout << "Circle::~Circle()" << endl;
}

double Circle::Area() const
{
    cout << "Circle::Area()" << endl;
}

void Circle::showValue() const
{
    cout << "circle : ";
    BaseEllipse::showValue();
    cout << "r = " << r << endl;
}


#endif