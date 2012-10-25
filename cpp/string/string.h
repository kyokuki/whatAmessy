// string.h

#include <iostream>
using std::ostream;
using std::istream;

#ifndef STRING_H
#define STRING_H

class String
{

public:
    String(const char* str=NULL);       //默认构造函数（无参数或有默认参数）
    String(const String& other);        //拷贝构造函数
    virtual ~String();                  //虚析构函数，virtual 声明能够让派生类的此函数都成为虚函数，并且按照派生类到基类的顺序自动正确析构
    int length() const { return len; }
    
    //操作符重载
    String & operator=(const String& other);
    String & operator=(const char * str);
    char & operator[](int i);
    const char & operator[](int i) const;
    
    //友元函数：必须在函数声明中使用friend关键子，函数定义中可以不用friend关键字
    //将operator==声明为友元是为了能够让【“adsfgcd” == string】正常工作，拷贝构造函数会用字符串生成临时对象
    friend bool operator==(const String& st, const String& other);
    friend bool operator>(const String& st, const String& other);
    friend bool operator<(const String& st, const String& other);
    friend ostream & operator<<(ostream & os, const String & str);
    friend istream & operator>>(istream & is, String & str);
    
    friend String  operator+(const String & st, const String &other);
    String  & operator+=(const String &other);
    
    
    // 静态方法：函数末尾居然也不能使用const，也许：const是防止方法修改成员变量，静态方法只能访问静态成员变量
    static int HowMany() { return num_strings; }
    

private:
    char* m_data;
    int len;
    static int num_strings;
public:
    static const int CINLIM = 80;
};

#endif // STRING_H
