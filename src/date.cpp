#include <iostream>
#include <string>
#include "date.h"

using namespace std;


date::date()
{
    day=1;
    month=1;
    year=1300;
}
/////////////////////////////////////////////
date::date(int d,int m,int y)
{
    set_date(d,m,y);
}
/////////////////////////////////////////////
bool date::is_leap_year()
{
    int r=year%33;
    if(r==1||r==5||r==9||r==13||r==17||r==22||r==26||r==30)
        return true;
    return false;
}
/////////////////////////////////////////////
bool date::is_leap_year(int y)
{
    int r = y % 33 ;
    if(r==1||r==5||r==9||r==13||r==17||r==22||r==26||r==30)
        return true;
    return false;
}
/////////////////////////////////////////////
bool is_leap_year(int year)
{
    int r=year%33;
    if(r==1||r==5||r==9||r==13||r==17||r==22||r==26||r==30)
        return true;
    return false;
}
/////////////////////////////////////////////
bool is_valid_date(int day,int month,int year)
{
    if(month<=6 && month>0 && day<=31 && day>0)
        return true;
    if(month<=11 && 7 <= month && day<=30 && day>0)
        return true;
    if(month==12 && is_leap_year(year) && day<=29 && day>0)
        return true;
    if(month==12 && !is_leap_year(year) && day<=30 && day>0)
        return true;
    return false;
}
/////////////////////////////////////////////
void date::set_date(int d,int m,int y)
{
    if(is_valid_date(d,m,y))
    {
        day=d;
        month=m;
        year=y;
    }
    else
        {
            //throw some exeption;
        }
}
/////////////////////////////////////////////
bool date::is_end_of_the_month()
{
    if((month<7 && day==31) || (month>6 &&  day ==30) || (month==12 && is_leap_year() && day ==29))
        return true;
    else
        return false;
}
/////////////////////////////////////////////
bool date::is_end_of_year()
{
    if(month==12 && (day==30 || (is_leap_year() && day==29)))
        return true;
    return false;

}
/////////////////////////////////////////////
void date::inc_one_day()
{
    if(!is_end_of_the_month())
        day++;
    else if(is_end_of_the_month() && !is_end_of_year())
    {
        month++;
        day=1;
    }
    else if(is_end_of_year())
    {
        year++;
        month=1;
        day=1;
    }
}
/////////////////////////////////////////////
void date::print_date()
{
    cout<<year<<'/'<<month<<'/'<<day;
}
/////////////////////////////////////////////
date str_to_date(string s)
{
    date dd;
    int y = std::stoi(s);
    int slash_pos=s.find('/');
    s=s.substr(slash_pos+1);
    int m=std::stoi(s);
    slash_pos=s.find('/');
    s=s.substr(slash_pos+1);
    int d=stoi(s);
    ///////////////////////////////
    dd.set_date(d,m,y);
    ///////////////////////////////
    return dd;
}
/////////////////////////////////////////////
ostream& operator<<(ostream &out,date d)
{
    out<<d.get_year()<<'/'<<d.get_month()<<'/'<<d.get_day();
    return out;
}
/////////////////////////////////////////////
istream& operator>>(istream &in,date& d)
{
    string s;
    in >> s;
    int year = stoi(s.substr(0,s.find('/')));
    s = s.substr(s.find('/')+1);
    int month = stoi(s.substr(0,s.find('/')));
    s = s.substr(0,s.find('/')+1);
    int day = stoi(s);
    d.set_date(year,month,day);
}
