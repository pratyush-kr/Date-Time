#include<iostream>
#include<string>
#include<ctime>

#define YEAR_MIN 1000
#define YEAR_MAX 3000

class Date;
class Time;

class Date
{
    protected:
        unsigned int day; //day of week
        unsigned int month; //month of year
        unsigned int date; //date of month
        unsigned int year; //year
    public:
        bool check_leap(int);
        Date(const int &, const int &, const int &, const int);//Date, Month, Year
        Date() {date = month = 1, year = 1970;}
        int dayofweek();
        void show() {printf("%02d-%02d-%d\n", date, month, year);}
        friend std::ostream& operator << (std::ostream &, const Date &);
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
        void show(){printf("%02x:%02x:%02x\n", hrs, min, sec);}
        Time(){hrs = min = sec = 0;}
        friend std::ostream& operator <<(std::ostream &, const Time &);
        friend std::istream& operator >>(std::istream &, Time &);
}pivot;

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
    day = (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
    return day;
}

std::ostream& operator <<(std::ostream &out, const Time &t)
{
    std::string str = "";
    if(t.hrs <= 9)
        str += '0';
    str += std::to_string(t.hrs);
    out<<str<<":";
    str = "";
    if(t.min <= 9)
        str += '0';
    str += std::to_string(t.min);
    out<<str<<":";
    str = "";
    if(t.sec <= 9)
        str += '0';
    str += std::to_string(t.sec);
    out<<str;
    return out;
}

std::istream& operator >>(std::istream &in, Time &t)
{
    in>>t.hrs>>t.min>>t.sec;
    return in;
}

std::ostream& operator << (std::ostream& out, const Date &d)
{
    std::string str="";
    std::string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct" "Nov", "Dec"};
    std::string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    out<<days[d.day]<<" ";
    if(d.date%10 == 1)
    {
        if(d.date <= 9)
            str += '0';
        str += std::to_string(d.date);
        out<<str<<"st ";
        str = "";
    }
    else if(d.date%10 == 2)
    {
        if(d.date <= 9)
            str += '0';
        str += std::to_string(d.date);
        out<<str<<"'nd ";
        str = "";
    }
    else if(d.date%10 == 3)
    {
        if(d.date <= 9)
            str += '0';
        str += std::to_string(d.date);
        out<<str<<"'rd ";
        str = "";
    }
    else
    {
        if(d.date <= 9)
            str += '0';
        str += std::to_string(d.date);
        out<<str<<"'th ";
        str = "";
    }
    out<<months[d.month-1]<<" ";
    out<<d.year;
    return out;
}

bool Date::check_leap(int year = 0)
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