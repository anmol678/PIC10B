/*****************************************************************
 Anmol Jain
 April 12, 2016.
 Interface of class time and definition of overloaded 
 friend operators.
 *****************************************************************/
#include <iostream>
#include <iomanip>

using std::ostream;

#ifndef time_h
#define time_h

class Time {
public:
    //Constructors - default and parameterised
    Time();
    Time(int m);
    Time(int h, int m);
    Time(double h);
    
    //Mutators - set the values of private variables mins and hrs
    void set_minutes(double m);
    void set_hours(double h);
    
    //Accessors - return the values of private variables mins and hrs
    int minutes() const;
    int hours() const;
    
    //Updates an object of class Time by adding 'x' minutes/hours
    Time& operator+=(double x);
    
    //Mutators for static variables - modify the values of private static variables
    static void set_hr_in_day(int x);
    static void set_min_in_hr(int x);
    
    //Accessors for static variables - return the values of private static variables
    static int get_hr_in_day();
    static int get_min_in_hr();
    
    //Non-member friend functions:
    //Operator overloading - Adds two Time objects
    friend Time operator+(const Time& a, const Time& b);
    
    //Comparison operators overloaded in order to compare two Time objects
    friend bool operator<(const Time& a, const Time& b);
    friend bool operator<=(const Time& a, const Time& b);
    friend bool operator==(const Time& a, const Time& b);
    friend bool operator!=(const Time& a, const Time& b);
    friend bool operator>=(const Time& a, const Time& b);
    friend bool operator>(const Time& a, const Time& b);
    
    //Output
    friend ostream& operator<<(ostream& out, const Time& a);
private:
    //private member functions
    
    //this function converts the variable 'x' into its proper form depending on the converting_factor
    int converter(int x, int converting_factor);
    
    //this function checks if hours is equal to hours in a day and changes it to 0
    //for example: if time = 24:00, midnight_check will change it to 0:00
    void midnight_check(int& h);
   
    //Compares two Time objects and returns an integer value based on the comparison
    int compare(const Time& b) const;

    //private fields
    int mins; //stores the value of minutes
    int hrs; //stores the value of hours
    
    static int hr_in_day; //static variable stores the number of hours in a day
    static int min_in_hr; //static variable stores the number of minutes in an hour
};

#endif
