#ifndef DATE_H
#define DATE_H

#include <string>

struct Date{
    int day, month, year;

    static int getAmountDaysOfMonth(int, int);

    void create();
    bool isValid();
    void aWeekAfter();
    std::string toString();
    int operator - (const Date);
    void operator = (const Date);
};

#endif