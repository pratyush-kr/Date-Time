#include<iostream>

#define YEAR_MIN 1000
#define YEAR_MAX 3000

class Date
{
    protected:
        unsigned int day; //day of week
        unsigned int month; //month of year
        unsigned int date; //date of month
        unsigned int year; //year
    public:
        bool check_leap(int year = 0)
        {
            if(year == 0)
                year = this->year;
            if(year%100 !=0 && year%4 == 0) //non centuary year and divisible by 4
                return true;
            else if(year%100 == 0 && year%400 == 0) //centuary year and divisible by 400
                return true;
            else
                return false;
        }
        Date(const int &, const int &, const int &, const int);//Date, Month, Year
        Date()
        {
            date = 1;
            month = 1;
            year = YEAR_MIN;
        }
        int dayofweek();
        void show()
        {
            std::cout<<date<<"-"<<month<<"-"<<year<<'\n';
        }
};

class Time : public Date
{
    protected:
        unsigned int hrs;
        unsigned int min;
        unsigned int sec;
    public:
        Time(const int h, const int m, const int s)
        {hrs = h, min = m, sec = s;}
    
};

Date::Date(const int &date, const int &month, 
            const int &year, const int day = 0) //Date, Month, Year
{
    if((date > 31 || date <1) || (month > 12 || month < 1) || (year<YEAR_MIN || year>YEAR_MAX))
    {
        std::cout<<"This date don't exists\n";
        return;
    }
    //if(date == 31 then months are odd upto 7 and even upto 12)
    if((month%2 == 1 && month <= 7) || (month%2 == 0 && month >= 8)) // checks all months with 31 days
        std::cout<<"";
    else if((month%2 == 1 && month >= 8) || (month%2 == 0 && month<=7)) //checks all months with 28,29 && 30 days
    {
        if(month == 2)
        {
            if(check_leap(year) == false && date > 28)
            {
                std::cout<<"Normal Years can't have more than 28 days in Feb\n";
                return;
            }
            else if(date > 29)
            {
                std::cout<<"Leap Years can't have more than 29 days in Feb\n";
                return;
            }
        }
        if(date > 30)
        {
            std::cout<<"This date don't exists\n";
            return;
        }
    }
    //now assign these values
    this->day = dayofweek();
    this->month = month;
    this->date = date;
    this->year = year;
}

int Date::dayofweek()
{
    int d = date, m = month, y = year;
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m<3;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}