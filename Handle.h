#ifndef HANDLE_H
#define HANDLE_H

//reference: https://stackoverflow.com/questions/21238806/how-to-set-output-console-width-in-visual-studio
//description: set size of the console with w (width), h (height)
//parameter: w and h, which must be larger than 0, are given in int data type
void setSizeConsole(int w, int h);

//description: read the key press of user and store it to s with limit in number of character
//parameter: txt in char* data type is the tool tip that help user know what information they should give
//parameter: s in char[] data type is the storage in which data from user is stored
//parameter: limit in int data type is used to limit the character stored in s
void s_input(const char* txt, char s[], int limit);

//description: compare 2 array of char, return true if they are equal
//parameter: a and b are given in char[] data type
bool isEqual(char a[], char b[]);

//description: generate ID for books and readers base on their index
//parameter: n, which is given in int data type, is the index
//parameter: s, whichs is given in char[] data type, is the storage which stores the ID
void idGeneration(int n, char s[]);

//description: convert char[] to int and return the number
//parameter: s, which is given in char[] data type, is the char[] that need to be converted to int
int parseInt(char s[]);

#endif