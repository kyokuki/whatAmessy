// main.cpp

#include <iostream>
#include "ellipse.h"
#include "circle.h"
using namespace std;

int main(void)
{
    Ellipse e;
    e.Area();
    e.showValue();
    
    Circle c;
    c.Area();
    c.showValue();
}
