#ifndef DATE_H
#define DATE_H

struct Date{
    int day, month, year;

    static int getAmountDaysOfMonth(int, int);

    void create();
    bool isValid();
    void aWeekAfter();
    int operator - (const Date);
    void operator = (const Date);
};

#endif