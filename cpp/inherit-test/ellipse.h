// ellipse.h

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <iostream>
#include "base_ellipse.h"
using std::cout;
using std::endl;

class Ellipse: public BaseEllipse               //共有继承基类
{
public:
    Ellipse(double x0=0, double y0=0, double a0 = 0, double b0 = 0, double angle0 = 0);
    virtual ~Ellipse();
    virtual double Area() const;                 //基类的此方法virtual为虚拟方法，这里加不加virtual都一样，加上直观
    virtual void showValue() const;
    
private:
    double a;
    double b;
    double angle;
};

Ellipse::Ellipse(double x0, double y0, double a0, double b0, double angle0) : BaseEllipse(x0,y0)    //使用了成员初回四化列表
{
    a = a0;
    b = b0;
    angle = angle0;
    cout << "Ellipse(double, double...)" << endl;
}

Ellipse::~Ellipse()
{
    cout << "~Ellipse()" << endl;
}

double Ellipse::Area() const
{
    cout << "Ellipse::Area()" << endl;
}

void Ellipse::showValue() const
{
    cout << "ellipse : ";
    BaseEllipse::showValue();
    cout << "a = " << a << ", " << "b = " << b << ", " << "angle = " << angle << endl;
}

#endif