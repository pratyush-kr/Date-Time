#include<iostream>
#include<string>
#include<ctime>

#define YEAR_MIN 1000
#define YEAR_MAX 3000

class Date;
class Time;

namespace mdc // mdc = month day cycle
{
    static std::string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct" "Nov", "Dec"};
    static std::string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
}

class Date
{
    protected:
        unsigned int day; //day of week
        unsigned int month; //month of year
        unsigned int date; //date of month
        unsigned int year; //year
    public:
        bool check_leap(int); //takes a year as an Integer and returns 1 if it is a leap year
        Date(const int &, const int &, const int &);//Date, Month, Year
        Date();//sets default to present Date
        int dayofweek(); //return 0 for Sun 1 for Mon and so on
        void show();//shows date in Www dddd Mmm yyyy
        friend std::ostream& operator << (std::ostream &, const Date &);//date in day dd.st mmm yyyy
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
        void show() {printf("%02d:%02d:%02d\n", hrs, min, sec);}
        Time()
        {
            time_t now = time(0);
            std::string str = (std::string)ctime(&now);
            //str contains time in the format :-
            //Www Mmm dd hh::mm::ss yyyy
            //Getting hrs
            this->hrs = std::stoi(str.substr(11, 2));
            //Getting min
            this->min = std::stoi(str.substr(14, 2));
            //Getting sec
            this->sec = std::stoi(str.substr(17, 2));
        }
        friend std::ostream& operator <<(std::ostream &, const Time &);
        friend std::istream& operator >>(std::istream &, Time &);
};


//Date

Date::Date()
{
    time_t now = time(0);
    std::string str = (std::string)ctime(&now);
    //str contains time int the format :-
    //Www Mmm dd hh::mm::ss yyyy
    //Getting Date
    this->date = std::stoi(str.substr(8, 2));
    //Getting week day
    for(int i=0; i<7; i++)
        if(str.substr(0, 3) == mdc::days[i])
        {
            this->day = i;
            break;
        }
    //Getting Month
    for(int i=0; i<12; i++)
        if(str.substr(4, 3) == mdc::months[i])
        {
            this->month = i+1;
            break;
        }
    //Getting Year
    this->year = std::stoi(str.substr(20, 4));
}

//Constructor of Date
Date::Date(const int &date, const int &month, const int &year) //Date, Month, Year
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
    this->month = month;
    this->date = date;
    this->year = year;
    this->day = dayofweek();
}


int Date::dayofweek()
{
    int d = date, m = month, y = year;
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m<3;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
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

void Date::show()
{
    std::string str="";
    std::cout<<mdc::days[day]<<" ";
    if(date%10 == 1)
    {
        if(date <= 9)
            str += '0';
        str += std::to_string(date);
        std::cout<<str<<"st ";
        str = "";
    }
    else if(date%10 == 2)
    {
        if(date <= 9)
            str += '0';
        str += std::to_string(date);
        std::cout<<str<<"nd ";
        str = "";
    }
    else if(date%10 == 3)
    {
        if(date <= 9)
            str += '0';
        str += std::to_string(date);
        std::cout<<str<<"rd ";
        str = "";
    }
    else
    {
        if(date <= 9)
            str += '0';
        str += std::to_string(date);
        std::cout<<str<<"th ";
        str = "";
    }
    std::cout<<mdc::months[month-1]<<" ";
    std::cout<<year<<'\n';
}

//End of Date


//Time


//End of Time


std::ostream& operator << (std::ostream &out, const Date &d)
{
    std::string str="";
    out<<mdc::days[d.day]<<" ";
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
        out<<str<<"nd ";
        str = "";
    }
    else if(d.date%10 == 3)
    {
        if(d.date <= 9)
            str += '0';
        str += std::to_string(d.date);
        out<<str<<"rd ";
        str = "";
    }
    else
    {
        if(d.date <= 9)
            str += '0';
        str += std::to_string(d.date);
        out<<str<<"th ";
        str = "";
    }
    out<<mdc::months[d.month-1]<<" ";
    out<<d.year;
    return out;
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