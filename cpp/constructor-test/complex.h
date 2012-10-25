// complex.h


#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
using namespace std;

class Complex
{
    private:
        
    double m_real;
    double m_imag;
    int id;
    static int counter;
        
    public:
    
    //默认构造函数 
    Complex()
    {
        m_real = 0.0;
        m_imag = 0.0;
        id = (++counter);
        cout<<"Complex(void) : id = "<<id<<endl;
    }
    
    //一般构造函数 
    Complex(double real, double imag)
    {
        m_real = real;
        m_imag = imag;
        id = (++counter);
        cout<<"Complex(double,double) : id = "<<id<<endl;   
    }
    
    //拷贝构造函数
    Complex(const Complex &other)
    {
        m_real = other.m_real;
        m_imag = other.m_imag;
        id = (++counter);
        cout<<"Complex(const Complex&) : id = "<<id<<" from id = "<<other.id<<endl; 
    } 
    
    //类型转换构造函数
    Complex(double real)
    {
        m_real = real;
        m_imag = 0.0;
        id = (++counter);
        cout<<"Complex(double) : id = "<<id<<endl;
    }
    
    //赋值运算符重载
    Complex &operator=(const Complex &other)
    {
        if (this == &other)
            return *this;
        
        this->m_real = other.m_real;
        this->m_imag = other.m_imag;
        cout<<"operator=(const Complex &) : id = "<<this->id<<" from id = "<<other.id<<endl;
        
        return *this;
    }
    
    //析构函数
    ~Complex()
    {
        cout<<"~Complex() : id = "<<id<<endl;
    } 
};

#endif // COMPLEX_H
