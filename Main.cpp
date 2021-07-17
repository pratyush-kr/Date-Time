#include "DateTime.h"
#include<iostream>

int main()
{
    Date d(15, 11, 1999);
    d.show();
    Time t(9, 52, 0);
    std::cout<<t<<'\n';
    std::cout<<d<<'\n';
    return 0;
}