// baseEllipse.h

#ifndef BASE_ELLIPSE_H
#define BASE_ELLIPSE_H

#include <iostream>
using std::cout;
using std::endl;

class BaseEllipse
{
public:
    BaseEllipse(double x0=0, double y0=0);
    virtual ~BaseEllipse();                                    //virtual 关键字只能用在类内函数声明处，用在类外则编译出错
    void Move(int nx, int ny) { x = nx; y = ny; }               //这个是内联函数。以下方法可定义内联函数：1.声明函数时并定义函数 2.在函数声明前加上inline关键字 3.在函数定义前加上关键字inline
    virtual double Area() const = 0;                            //这个是纯虚函数，纯虚函数声明的结尾处是“=0”。
                                                                 //当类中包含纯虚函数时，则不能创建该类的对象，包含纯虚函数的 类只能用作基类。
                                                                 //可以void Move(int nx, int ny) = 0； 声明为虚拟函数，指出类是个抽象基类，在类中该函数可以不定义
    virtual void showValue() const = 0;
   
private:
    double x;       //x坐标
    double y;       //y坐标

};

BaseEllipse::BaseEllipse(double x0, double y0)                 //函数声明处已经有默认参数值了，这里如果再写上则会编译出错
{ 
    x = x0;
    y = y0;
    cout << "BaseEllipse::BaseEllipse(double, double)" << endl;
}

BaseEllipse::~BaseEllipse()
{
    cout << "BaseEllipse::~BaseEllipse()" << endl;
}

double BaseEllipse::Area() const
{
    cout << "BaseEllipse::Area()";
}

void BaseEllipse::showValue() const
{
    cout <<  "x = " << x << ", " << "y = " << y << ", ";
}
#endif