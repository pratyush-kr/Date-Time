#include "DateTime.h"
#include<iostream>

int main()
{
    Date d(17, 7, 2021);
    d.show();
    Time t(9, 52, 0);
    time_t now = time(0);
    std::cout<<ctime(&now)<<'\n';
    std::cout<<d<<'\n';
    return 0;
}