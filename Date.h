#ifndef DATE_H
#define DATE_H

struct Date{
    int day, month, year;

    //description: calculate and return number of day in that month
    //parameter 1: month needed to be calculate
    //parameter 2: year to check if it is leap year
    int getAmountDaysOfMonth(int, int);

    //description: take date data from user
    void create();

    //description: check if date is valid then return true otherwise false
    bool isValid();

    //description: calculate a week after this date and store it to this oject
    void aWeekAfter();

    //description: return a string of date in dd/mm/yyyy format
    const char* toString();

    //description: overload operator minus to calculate the date different in days
    //parameter: date that need to be calculated with
    int operator - (const Date);

    //description: overload operator equal to copy other Date variable to this variable
    //parameter: date that is used to copy its data
    void operator = (const Date);
};

#endif