/*****************************************************************
 Anmol Jain
 April 12, 2016.
 Implementation of class time and definition of overloaded
 friend operators.
 *****************************************************************/
#include "time.h"

//static variables are intialized
int Time::hr_in_day = 24;
int Time::min_in_hr = 60;

int flag1 = 0, flag2 = 0;//global variables - used as markers to indicate the flow of the program and ensure desired implementation

//Note: purpose of midnight_check and converter functions has already been specified. these two functions re-occur through the course of the program.
//Default constructor: sets the value of hrs and mins to 0
Time::Time() : hrs(0), mins(0){}

//Parameterized constructor: accepts integer value of minutes, converts and stores values in hrs and mins variables
Time::Time(int m) : hrs( m / min_in_hr), mins(m % min_in_hr)
{
    midnight_check(hrs);
    flag1 = 1;
}

//Parameterized constructor: accepts integer value of minutes and hours, converts and stores values in hrs and mins variables
Time::Time(int h, int m) : hrs((m / min_in_hr) + converter(h, hr_in_day)), mins(converter(m, min_in_hr))
{
    midnight_check(hrs);
    flag1 = 1;
}

//Parameterized constructor: accepts double value of hours, converts and stores values in hrs and mins variables
Time::Time(double h)
{
    int hr = static_cast<int>(h);
    hrs = converter(h, hr_in_day);
    midnight_check(hrs);
    mins = static_cast<int>(((h - hr) * min_in_hr) + 0.5);
    flag1 = 1;
}

//Mutator: sets the value of private variable mins representing minutes
void Time::set_minutes(double m)
{
    int x = static_cast<int>(m + 0.5);
    mins = converter(x, min_in_hr);
}

//Mutator: sets the value of private variable hrs representing hours
void Time::set_hours(double h)
{
    int x = static_cast<int>(h);
    hrs = converter(x, hr_in_day);
    midnight_check(hrs);
}

//Accessor: returns integer value of private variable mins
int Time::minutes() const
{
    return mins;
}

//Accessor: Returns integer value of private variable hrs
int Time::hours() const
{
    return hrs;
}

//Operator overloading: updates (since it is called by reference) a Time object by adding 'x' minutes/hours
Time& Time::operator+=(double x)
{
    int y = static_cast<int>(x);
    
    if (x == y)
        this->mins += y;
    else
        this->mins += static_cast<int>((x * min_in_hr) + 0.5);//minutes are rounded off if 'x' contains a decimal value
    
    //to make sure that a legal time is displayed - if minutes exceed the number of minutes in an hour, the hrs and mins values are modified accordingly
    if (this->mins >= min_in_hr)
    {
        y = mins / min_in_hr;
        hrs += y;
        mins %= min_in_hr;
    }
    midnight_check(hrs);
    return *this;
}

//Mutator: modifies the value of static variable that stores the number of hours in a day
void Time::set_hr_in_day(int x)
{
    int* p = &hr_in_day;
    *p = x;
}

//Mutator: modifies the value of static variable that stores the number of minutes in an hour
void Time::set_min_in_hr(int x)
{
    int* p = &min_in_hr;
    *p = x;
    
    //if Time objects have'nt been intialised before static varible is altered then flag2 is set to 1
    if (flag1 == 0)
        flag2 = 1;
}

//Accessor: returns integer value of static variable that stores the number of hours in a day
int Time::get_hr_in_day()
{
    return hr_in_day;
}

//Accessor: returns integer value of static variable that stores the number of minutes in an hour
int Time::get_min_in_hr()
{
    return min_in_hr;
}

//Operator overloading: adds two Time objects and converts them into legal form thereafter
Time operator+(const Time& a, const Time& b)
{
    //Values of both Time objects are converted to their equivalent of minutes and the total minutes are calculated
    int a_minutes = (a.hours() * Time::get_min_in_hr()) + a.minutes();
    int b_minutes = (b.hours() * Time::get_min_in_hr()) + b.minutes();
    int tot_minutes = a_minutes + b_minutes;
    
    //Thereafter, minutes are converted and restored into their original Time form
    if (tot_minutes >= Time::get_min_in_hr())
        return Time((tot_minutes / Time::get_min_in_hr()),(tot_minutes % Time::get_min_in_hr()));
    else
        return Time(0, tot_minutes);
}

//Comparison operator: employs private function 'compare' to compare two Time objects
bool operator<(const Time& a, const Time& b)
{
    return a.compare(b) == -1;
}

//Comparison operator: employs private function 'compare' to compare two Time objects
bool operator<=(const Time& a, const Time& b)
{
    return (a.compare(b) == -1 || a.compare(b) == 0);
}

//Comparison operator: employs private function 'compare' to compare two Time objects
bool operator==(const Time& a, const Time& b)
{
    return (a.compare(b) == 0);
}

//Comparison operator: employs private function 'compare' to compare two Time objects
bool operator!=(const Time& a, const Time& b)
{
    return (a.compare(b) == 1 || a.compare(b) == -1);
}

//Comparison operator: employs private function 'compare' to compare two Time objects
bool operator>(const Time& a, const Time& b)
{
    return a.compare(b) == 1;
}

//Comparison operator: employs private function 'compare' to compare two Time objects
bool operator>=(const Time& a, const Time& b)
{
    return (a.compare(b) == 1 || a.compare(b) == 0);
}

/*Time operator-(const Time& a, const Time& b)
{
}*/

//Output operator overloading: operator << is overloaded to ensure that all Time objects are displayed in proper format
ostream& operator<<(ostream& out, const Time& a)
{
    if (flag2 == 0)//flag2 is equal to 0 if Time objects were intialized before the static variables of conversion were altered, implying that Time objects were created in accordance with default values of static variables
    {
        int temp_min = a.hours() * 60 + a.minutes();
        out << temp_min / a.get_min_in_hr() << ":";
        out << std::setw(2) << std::setfill('0') << temp_min % a.get_min_in_hr();
        return out;
    }
    out << a.hours() << ":";
    out << std::setw(2) << std::setfill('0') << a.minutes();
    return out;
}

//Private member function: this function converts the variable 'x' into its proper form depending on the converting_factor
int Time::converter(int x, int converting_factor)
{
    if (x >= converting_factor)
        return x % converting_factor;
    else
        return x;
}

//Private member function: this function checks if hours is equal to hours_in_a_day and changes it to 0
void Time::midnight_check(int& h)
{
    if (h == hr_in_day)
        h = 0;
}

//Private member function: compares two Time objects and returns an integer value based on the comparison
//-1 if object on the right is greater than object on left, 1 if object on right is smaller than object on left and 0 if the two objects are equal
int Time::compare(const Time& b) const
{
    if (this->hrs < b.hrs)
        return -1;
    else if (this->hrs > b.hrs)
        return 1;
    else
    {
        if (this->mins < b.mins)
            return -1;
        else if (this->mins > b.mins)
            return 1;
        else
            return 0;
    }
}