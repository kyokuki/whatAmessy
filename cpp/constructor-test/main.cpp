// main.cpp

#include <string>
#include "complex.h"

int Complex::counter=0;
Complex test1(const Complex& c)
{
    return c;
}

Complex test2(const Complex c)
{
    return c;
}

Complex test3()
{
    static Complex c(1.0, 5.0);
    return c;
}

Complex& test4()
{
    static Complex c(1.0, 5.0);
    return c;
}

int main()
{
    Complex a,b;
    
    //下面函数执行过程中各会调用几次构造函数，调用的是什么构造函数？
    Complex c=test1(a);
    Complex d=test2(a);

    b = test3();
    b = test4();

    Complex e=test1(1.2);
    Complex f=test2(1.2);
    
    string str = "adafsdf--";
    str += str;
    cout << str << endl;
    cout << "-----------" << endl;
}

/*
以下是测试内容：

1.
int main()
{
    Complex a,b;
    
    test1(a);
    test2(b);
} 
输出：

Complex(void) : id = 1
Complex(void) : id = 2
Complex(const Complex&) : id = 3 from id = 1    //test1参数是引用传递，返回是值返回，拷贝构造函数复制id=1生成临时实例id=3用以返回 
~Complex() : id = 3                             //返回值未保存而析构 
Complex(const Complex&) : id = 4 from id = 2    //test2参数是值传递，拷贝构造函数复制参数id=1生成临时实例id=4 
Complex(const Complex&) : id = 5 from id = 4    //test2值返回， 拷贝构造函数复制临时实例id=4，生成id=5 
~Complex() : id = 5                             //返回值为保存而析构 
~Complex() : id = 4                             //test2内的临时实例接着析构 
~Complex() : id = 2
~Complex() : id = 1

----------------------------------

2.
int main()
{
    Complex a,b;
    
    b = test3();
    b = test4();
} 
输出：
Complex(void) : id = 1
Complex(void) : id = 2
Complex(double,double) : id = 3                     //test3生成静态实例id=3 
Complex(const Complex&) : id = 4 from id = 3        //test3是指返回，所以拷贝构造函数生成临时实例 id=4 
operator=(const Complex &) : id = 2 from id = 4     //赋值运算符从临时实例id=4复制到实例id=2 
~Complex() : id = 4                                 //临时实例id=4析构 
Complex(double,double) : id = 5                     //test4中生成静态实例id=5 ，因为返回值是引用，所以直接返回静态实例id=5 
operator=(const Complex &) : id = 2 from id = 5     //赋值运算符从静态实例id=5复制到实例id=2 
~Complex() : id = 2                                 
~Complex() : id = 1                                 //实例按照生成顺序的相反顺序析构 
~Complex() : id = 5
~Complex() : id = 3                                 //静态实例最后析构，按照静态实例生成顺序的相反顺序析构 

--------------------------------

3.
int main()
{
    Complex a,b;
    
    Complex c = test1(1.2);                         //test1(Complex(1.2))与test(1.2)等价 
    Complex d = test2(1.2);
} 
输出：
Complex(void) : id = 1
Complex(void) : id = 2
Complex(double) : id = 3                            //test1(1.2)先调用类型转换函数生成临时实例id=3 
Complex(const Complex&) : id = 4 from id = 3        //拷贝构造函数 从 test1的引用参数同时也是临时实例id=3 复制生成另一实例id=4，即c 
~Complex() : id = 3                                 //临时实例id=3析构 
Complex(double) : id = 5                            //test2(1.2)先调用类型转换函数生成临时实例id=5 
Complex(const Complex&) : id = 6 from id = 5        //拷贝构造函数 从 test2的值参数同时也是临时实例id=5 复制生成另一实例id=6 ，即d 
~Complex() : id = 5                                 //临时实例id=5析构 
~Complex() : id = 6                                 
~Complex() : id = 4
~Complex() : id = 2
~Complex() : id = 1                                 // 保存下来的实例按照生成顺序的相反顺序析构  

--------------------------------
*/

