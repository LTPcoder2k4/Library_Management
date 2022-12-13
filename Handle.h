#ifndef HANDLE_H
#define HANDLE_H

//description: read the key press of user and store it to s with limit in number of character
//parameter: txt in char* data type is the tool tip that help user know what information they should give
//parameter: s in char[] data type is the storage in which data from user is stored
//parameter: limit in int data type is used to limit the character stored in s
void s_input(const char* txt, char s[], int limit);

//description: compare 2 array of char, return true if they are equal
//parameter: a and b are given in char[] data type
bool isEqual(char a[], char b[]);

//description: swap the value of the 2 storages a and b
//parameter: a and b are given in char[] data type
void swap(char a[], char b[]);
//description: overload the function swap the value of the 2 storages a and b
//parameter: a and b are given in char data type
void swap(char& a, char& b);
//description: overload the function swap the value of the 2 storages a and b
//parameter: a and b are given in bool data type
void swap(bool& a, bool& b);

//description: generate ID for books and readers base on their index
//parameter: n, which is given in int data type, is the index
//parameter: s, whichs is given in char[] data type, is the storage which stores the ID
void idGeneration(int n, char s[]);

//description: convert char[] to int and return the number
//parameter: s, which is given in char[] data type, is the char[] that need to be converted to int
//parameter: n, which is given in int data type, is size of s
int parseInt(char s[], int n);

//description: convert int to char[]
//parameter: s, which is given in char[] data type, is the result of the convertation
//parameter: i, which is given in int data type, is the number that need to be converted
void toString(char s[], int i);

//description: copy s to res
//parameter: s and res are given in char[] data type
void substring(char s[], char res[]);
//description: overloading copy s to res with the specified location of s
//parameter: s and res are given in char[] data type
//parameter: start and end, which are given in int data type, are start of substring and end of substring respectively
void substring(char s[], char res[], int start, int end);
//description: overloading copy s to res with the specified location of s and res
//parameter: s and res are given in char[] data type
//parameter: start and end, which are given in int data type, are start of substring and end of substring respectively
//parameter: start2, which is given in int data type, is start index of res that need to be copied to
void substring(char s[], char res[], int start, int end, int start2);

//description: return number of days in month
//parameter: month is given in int data type
//parameter: year, which is given in int data type, is used to check leap year
int getAmountDaysOfMonth(int month, int year);

//description: calculate a week after date
//parameter: date, which is in int[3] data type, is date in format [DD, MM, YYYY]
void aWeekAfter(int date[3]);

//description: calculate days different between date1 and date 2, return the number of days different
//parameter: date1 and date2, which are in int[3] data type, are date in format [DD, MM, YYYY]
int dateDifferent(int date1[3], int date2[3]);

//description: format the date and store into result
//parameter: date, which is in char[11] data type, is date in format "DD/MM/YYYY"
//parameter: result, which is in int[3] data type, is date in format [DD, MM, YYYY]
void dateFormat(char date[11], int result[3]);

#endif