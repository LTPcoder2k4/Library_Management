#include <conio.h>
#include <Windows.h>
#include <stdio.h>
#include "Handle.h"
#include <cstring>

void setSizeConsole(int w, int h)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, w, h, TRUE);
}

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
    if (strcmp(a, b) == 0) return true;
    return false;
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

int parseInt(char s[]){
    int i = 0;
    for (int digit = 0; digit < strlen(s); digit++) {
        if (s[digit] <= '9' && s[digit] >= '0') i = i * 10 + (s[digit] - '0');
        else throw 500;
    }
    return i;
}