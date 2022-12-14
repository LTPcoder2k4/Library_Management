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
        if (s[digit] <= '9' && s[digit] >= '0') i = i * 10 + (s[digit] - '0');
        else throw 500;
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