

#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <vector>


using namespace std;

class date
{
public:
    date();
    date(int d,int m,int y);
    void set_date(int d,int m,int y);
    int get_day(){return day;};
    int get_month(){return month;};
    int get_year(){return year;};
    bool is_leap_year();
    static bool is_leap_year(int y);
    bool is_end_of_the_month();
    bool is_end_of_year();
    void inc_one_day();
    void print_date();

    friend istream& operator>>(istream &in,date& d);
    friend ostream& operator<<(ostream &out,date d);

private:
    int day;
    int month;
    int year;
};

#endif // DATE_H
