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
int parseInt(char s[]);

//description: convert int to char[]
//parameter: s, which is given in char[] data type, is the result of the convertation
//parameter: i, which is given in int data type, is the number that need to be converted
void toString(char s[], int i);

#endif