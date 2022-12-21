#include "Date.h"
#include "Handle.h"
#include <stdio.h>

void Date::create(){
    char temp[4];

    //Input day and check if user type not number character
    inputDay:
    try{
        s_input("Input day: ", temp, 2);
        this->day = parseInt(temp, 2);
    }catch(int error){
        if (error == 500){
            printf("Day must be a number!\n");
            goto inputDay;
        }
    }

    //Input month and check if user type not number character
    inputMonth:
    try{
        s_input("Input month: ", temp, 2);
        this->month = parseInt(temp, 2);
    }catch(int error){
        if (error == 500){
            printf("Month must be a number!\n");
            goto inputMonth;
        }
    }

    //Input year and check if user type not number character
    inputYear:
    try{
        s_input("Input year: ", temp, 4);
        this->year = parseInt(temp, 4);
    }catch(int error){
        if (error == 500){
            printf("Year must be a number!\n");
            goto inputYear;
        }
    }

}

int Date::getAmountDaysOfMonth(int month, int year){
    switch (month) {
        // Group all 31 days cases together
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;

        // Group all 30 days cases together
        case 4: case 6: case 9: case 11: return 30;

        // Remaining case
        case 2:
            //Check Leap year, increase days of month if Feb
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                return 29;
            }
            return 28;

        // Invalid month
        default:
            return -1;
    }
}

bool Date::isValid(){
    if (this->day > this->getAmountDaysOfMonth(this->month, this->year)) return false;
    return true;
}

void Date::aWeekAfter(){
    int amountDaysOfMonth = getAmountDaysOfMonth(this->month, this->year);

    //Now add 7 days
    this->day = this->day + 7;

    //Check if it comes to new month
    if (this->day > amountDaysOfMonth) {
        this->day -= amountDaysOfMonth;
        this->month = this->month + 1;
    }
    else {
        this->month = this->month;
    }

    //Check if it comes to new year
    if (this->month > 12) {
        this->month -= 12;
        this->year = this->year + 1;
    }
}

const char* Date::toString(){
    static char date[11];
    date[0] = this->day / 10 + '0';
    date[1] = this->day % 10 + '0';
    date[2] = '/';
    date[3] = this->month / 10 + '0';
    date[4] = this->month % 10 + '0';
    date[5] = '/';
    date[6] = this->year / 1000 + '0';
    date[7] = this->year / 100 / 10 + '0';
    date[8] = this->year / 10 / 100 + '0';
    date[9] = this->year % 10 + '0';
    date[10] = '\0';
    return date;
}

//Subtraction operator overload to calculate date time different between couple days
int Date::operator - (const Date date){
    //Declare result date variable
    int day = 0, month = 0, year = 0;

    //Calculate year different
    year = this->year - date.year;

    if (this->month < date.month) {
        //If this month is lower than destination month
        //We will calculate the sum of days from this year to destination year
        for (int i = date.month; i <= 12; i++) {
            month += getAmountDaysOfMonth(i, date.year);
        }
        for (int i = 1; i < this->month; i++) {
            month += getAmountDaysOfMonth(i, this->year);
        }

        //We borrow 1 year to make the subtraction
        //So we will decrease year by 1 unit
        year--;
    }
    else {
        //Otherwise, get the subtraction as usual
        for (int i = date.month; i < this->month; i++) {
            month += getAmountDaysOfMonth(i, date.year);
        }
    }

    //Year multiply by 365 is total days
    year *= 365;

    if (this->day < date.day) {
        //If this day is lower than destination day
        //We will calculate the sum of days from this day to destination day
        day = this->day + getAmountDaysOfMonth(this->month == 1 ? 12 : this->month - 1, this->year) - date.day;
        
        //We borrow 1 month to make the subtraction
        //So we will decrease year by number of days in that month
        month -= getAmountDaysOfMonth(this->month == 1 ? 12 : this->month - 1, this->year);
    }
    else {
        //Otherwise, get the subtraction as usual
        day = this->day - date.day;
    }

    //The result is total day calculated from day, month, and year
    return day + month + year;
}

void Date::operator = (const Date date){
    this->day = date.day;
    this->month = date.month;
    this->year = date.year;
}