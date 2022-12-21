#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <wchar.h>
#include <conio.h>
#include <windows.h>
#include "Books.h"

//Main function is responsible for print main menu and navigate to smaller section
int main(){

    //ev is code of key press event in ascii
    int ev = 0;

    Stock stock;

    //27 is escape key
    //Main loop repeats until user press ESC
    while (ev != 27)
	{
		system("CLS");
        printf("{\\__/}\n");
        printf("( *.*)\n");

        //Change mode of console to U16TEXT in order to print ❤️
        int oldMode = _setmode(_fileno(stdout), 0x00020000);
        wprintf(L"/ > ❤️ \n");
        //Change it back to O_TEXT to print normal ascii character
        _setmode(_fileno(stdout), oldMode);

		printf("**********Menu**********\n");
		printf("* 1. Book section      *\n");
		printf("* 2. Reader section    *\n");
		printf("* 3. Card section      *\n");
		printf("* 4. Statistic section *\n");
		printf("* ESC. Exit            *\n");
		printf("************************");
		ev = _getch();

		switch (ev){
            case '1':
                stock.add();
                stock.push();
                break;
            case '2':
                
                break;
            case '3':

                break;
            case '4':
                
                break;
            default:
                break;
		}
	}
    return 0;
}