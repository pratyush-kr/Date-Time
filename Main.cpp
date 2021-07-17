#include "DateTime.h"
#include<iostream>
int main()
{
    Date d(16, 11, 1998);
    d.show();
    std::cout<<d.dayofweek()<<'\n';
    std::cout<<d.check_leap()<<'\n';
    Time t(9, 52, 0);
}