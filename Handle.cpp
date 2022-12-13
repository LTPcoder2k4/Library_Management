#include <conio.h>
#include <Windows.h>
#include <stdio.h>
#include "Handle.h"

void s_input(const char* txt, char s[], int limit){
    //Print the command text
	printf(txt);

    //Get the first key press of user
	char ev = _getch();
    int index = 0;

    //Take the key press until user press enter
    while (ev != '\r') {
        //Check if user press delete or backspace button
        if (ev == 127 || ev == 8) {
            //Check if can delete element
            if (index > 0) {
                s[--index] = 0;
                //Print backspace will delete the key press
                printf("\b \b");
            }
        }
        //Check if the character is not reach the limit
        else if (index < limit) {
            //Assign the key press to s char array
            s[index++] = ev;
            //Print the key press to screen
            printf("%c", ev);
        }

        //Take the key press
        ev = _getch();
    }
    //Assign end of string character to s char array
    s[index] = '\0';
    //Print newline when user press enter
    printf("%c", '\n');
}

bool isEqual(char a[], char b[]){
    for (int i = 0; i < 100; i++) 
    {
        if (a[i] != b[i]) return false;
        if (a[i] == '\0') return true;
    }
    return false;
}

void swap(char a[], char b[]){
    char t[100];

    substring(t, a);
    substring(a, b);
    substring(b, t);
}

void swap(char& a, char& b){
    char c = a;
    a = b;
    b = c;
}

void swap(bool& a, bool& b){
    bool c = a;
    a = b;
    b = c;
}

void idGeneration(int n, char s[]){
    if (n < 10) {
        s[2] = '0';
        s[3] = '0';
        s[4] = '0';
        s[5] = n + '0';
    }
    else if (n < 100) {
        s[2] = '0';
        s[3] = '0';
        s[4] = n / 10 + '0';
        s[5] = n % 10 + '0';
    }
    else if (n < 1000) {
        s[2] = '0';
        s[3] = n / 100 + '0';
        s[4] = n % 100 / 10 + '0';
        s[5] = n % 100 % 10 + '0';
    }
    else {
        s[2] = n / 1000 + '0';
        s[3] = n % 1000 / 100 + '0';
        s[4] = n % 1000 % 100 / 10 + '0';
        s[5] = n % 1000 % 100 % 10 + '0';
    }
}

int parseInt(char s[], int n){
    int i = 0;
    for (int digit = 0; digit < n; digit++) {
        if (s[digit] <= '9' && s[digit] >= '0')
            i = i * 10 + (s[digit] - '0');
    }
    return i;
}

void toString(char s[], int i){
    int index = 0;
    s[index++] = (i % 10) + '0';
    while (i /= 10){
        s[index++] = (i % 10) + '0';
    }

    index--;
    int index2 = 0;
    while (index > index2){
        swap(s[index--], s[index2++]);
    }
}

void substring(char s[], char res[]){
    for (int i = 0; i < 100; i++) 
    {
        res[i] = s[i];
        if (s[i] == '\0') return;
    }
}

void substring(char s[], char res[], int start, int end){
    int index = 0;
    for (int i = start; i < end; i++) 
    {
        res[index++] = s[i];
    }
}

void substring(char s[], char res[], int start, int end, int start2){
    int index = start2;
    for (int i = start; i < end; i++)
    {
        res[index++] = s[i];
    }
}

int getAmountDaysOfMonth(int month, int year) {
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

        // Invalid input
    default:
        return -1;
    }
}

void aWeekAfter(int date[3]) {
    int amountDaysOfMonth = getAmountDaysOfMonth(date[1], date[2]);

    //Now add 7 days
    date[0] = date[0] + 7;

    //Check if it comes to new month
    if (date[0] > amountDaysOfMonth) {
        date[0] -= amountDaysOfMonth;
        date[1] = date[1] + 1;
    }
    else {
        date[1] = date[1];
    }


    //Check if it comes to new year
    if (date[1] > 12) {
        date[1] -= 12;
        date[2] = date[2] + 1;
    }
}

int dateDifferent(int date1[3], int date2[3]) {

    int result[3] = { 0 };
    result[2] = date2[2] - date1[2];

    if (date2[1] < date1[1]) {
        for (int i = date1[1]; i <= 12; i++) {
            result[1] += getAmountDaysOfMonth(i, date1[2]);
        }
        for (int i = 1; i < date2[1]; i++) {
            result[1] += getAmountDaysOfMonth(i, date2[2]);
        }
        result[2]--;
    }
    else {
        for (int i = date1[1]; i < date2[1]; i++) {
            result[1] += getAmountDaysOfMonth(i, date2[2]);
        }
    }
    result[2] *= 365;

    if (date2[0] < date1[0]) {
        result[0] = date2[0] + getAmountDaysOfMonth(date2[1] == 1 ? 12 : date2[1] - 1, date2[2]) - date1[0];
        result[1] -= getAmountDaysOfMonth(date2[1] == 1 ? 12 : date2[1] - 1, date2[2]);

    }
    else {
        result[0] = date2[0] - date1[0];
    }
    return result[0] + result[1] + result[2];
}

void dateFormat(char date[11], int result[3]) {
    result[0] = (date[0] - '0') * 10 + (date[1] - '0'); //get day
    result[1] = (date[3] - '0') * 10 + (date[4] - '0'); //get month
    result[2] = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0'); //get year
}