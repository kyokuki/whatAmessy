// string.cpp

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "string.h"

using std::cerr;
using std::endl;
using std::strcpy;
using std::strlen;
using std::ostream;
using std::istream;

int String::num_strings = 0;

String::String(const char *str)
{
    if (str == NULL) {
        m_data = new char[1];
        m_data[0] = '\0';
        len = 1;
        num_strings++;
    } else {
        len = strlen(str);
        m_data =  new char[len+1];
        strcpy(m_data, str);
        num_strings++;
    }
}


String::String(const String& other)
{
    len = other.len;
    m_data =  new char[len+1];
    strcpy(m_data, other.m_data);
    num_strings++;
}

String::~String()
{
    --num_strings;
    delete [] m_data;
}

String& String::operator=(const String& other)
{
    if (this == &other) {
        return *this;
    }
        
    delete [] m_data;
    len = other.len;
    m_data =  new char[len+1];
    strcpy(m_data, other.m_data);
    m_data[len] = '\0';
    
    return *this;
}

String& String::operator=(const char * str)
{
    if (str == NULL) {
        return *this;
    }
        
    delete [] m_data;
    len = strlen(str);
    m_data =  new char[len+1];
    strcpy(m_data, str);
    
    return *this;
}

char & String::operator[](int i)
{
    if (i<0 || i>len) {
        cerr << "Error:" << i << " out of range." << endl;
        exit(1);
    }
        
    return m_data[i];
}

const char & String::operator[](int i) const
{
     if (i<0 || i>len) {
        cerr << "Error:" << i << " out of range." << endl;
        exit(1);
    }
    return m_data[i];
}

//友元函数不能在函数最后添加const，因为友元不是成员函数，加const的目的是防止成员函数修改成员变量
bool operator==(const String& st, const String& other)
{
    return (strcmp(st.m_data, other.m_data) == 0);
}

bool operator>(const String& st, const String& other)
{
    return (strcmp(st.m_data, other.m_data) > 0);
}

bool operator<(const String& st, const String& other)
{
    return (other.m_data > st.m_data);
}

// 声明成友元使【 String + "abcd.." 和 "abcd.." + String 】正常工作，但【“abcd..” + "efgh.."】不能正常工作.....不过<string>库也不能这样...
String  operator+(const String & st, const String &other)
{
    int length = st.length() + other.length();
    char*  temp = new char[length + 1];
    strcpy(temp, st.m_data);
    strcat(temp, other.m_data);
    String str(temp);
    delete [] temp;
    //返回是值返回，这里返回临时对象str，会调用拷贝构造函数（我这里写的是深度拷贝）生成一个str对象的副本用于返回值，之后str对象析构
    return str;
}

// 不是友元，【String += “abc..”】有意义，但【“abc...” = String】没意思
String & String::operator+=(const String &other)
{
    char *p = m_data;
    len = len + other.len;
    m_data =  new char[len + 1];
    strcpy(m_data, p);
    strcat(m_data, other.m_data);
    delete [] p;
    
    return *this;
}



// 函数声明中此函数为友元函数，返回引用是为了让"cout << String << String << endl;" 能正确工作
ostream & operator<< (ostream &os, const String &str)
{
    os << str.m_data;
    return os;
}


istream & operator>>(istream & is, String & str)
{
    char temp[String::CINLIM];
    is.get(temp, String::CINLIM);
    if (is) {
        str = temp;
    }
    while(is && is.get() != '\n') {
        continue;
    }
    
    return is;
}



#if 0
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    String string1;
    string1 = "string1";
    String string2("string2");
    String string3 = String(string2); 
    String string4;
    string4 = string3;
    String string5("string5");
    String string6("string6");
    
    cout << "string5 > string6 : " << (string5 > string6) << endl;
    cout <<  "string5[1] : " << string5[1] << endl;
    string5[1] = 'a';
    cout << string5 << endl;
    
    cout << "num_strings = " <<String::HowMany() << endl ;
    cout << " string + string : " <<  (string5 + "string6") << endl;
    
    string6 += "aaaaaaas";
    cout << string6 << endl;

    
}
#endif

