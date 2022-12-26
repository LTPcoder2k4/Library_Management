#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <wchar.h>
#include <conio.h>
#include <windows.h>
#include "Readers.h"
#include "Books.h"
#include "Handle.h"
#include "Cards.h"

void getAuthorize(char username[], char password[]){
    FILE* f = fopen("user.csv", "rb");
    if (f != NULL){
        fscanf(f, "%[^,],%[^,],\n", username, password);
    }
    fclose(f);
}

bool SignedIn(){
    system("CLS");

    char root_username[100], root_password[100];
    getAuthorize(root_username, root_password);

    char user_username[100], user_password[100];
    s_input("Username: ", user_username, 100);
    s_input("Password: ", user_password, 100);

    if (isEqual(root_username, user_username)){
        if (isEqual(root_password, user_password)){
            printf("Signed in successfully!");
            Sleep(1000);
            return true;
        }
    }
    printf("Username or password not found!");
    Sleep(1000);
    return false;
}

void booksPage(Stock &s){
    //ev is code of key press event in ascii
    int ev = 0;

    //27 is escape key
    //Main loop repeats until user press ESC
    while (ev != 27)
	{
		system("CLS");
		printf("********Book section********\n");
		printf("* 1. Add new book          *\n");
		printf("* 2. Display book in stock *\n");
		printf("* 3. Edit book             *\n");
		printf("* 4. Delete book           *\n");
		printf("* 5. Find book by ISBN     *\n");
		printf("* 6. Find book by name     *\n");
		printf("* ESC. Exit                *\n");
		printf("****************************");
		ev = _getch();

        char isbn[14], name[16];
        int index;

		switch (ev){
            case '1':
                s.add();
                break;
            case '2':
                s.display();
                break;
            case '3':
                system("CLS");
                s_input("ISBN of book you want to edit: ", isbn, 13);

                index = s.findID(isbn);
                if (index == -1){
                    printf("There is no book with the ISBN: %s!\n", isbn);
                }else{
                    s.books[index].edit();
                }
                break;
            case '4':
                system("CLS");
                s_input("ISBN of book you want to delete: ", isbn, 13);

                index = s.findID(isbn);
                if (index == -1){
                    printf("There is no book with the ISBN: %s!\n", isbn);
                }else{
                    s.remove(index);
                    printf("Book deleted!\n");
                    Sleep(1000);
                }
                break;
            case '5':
                system("CLS");
                s_input("ISBN of book you want to find: ", isbn, 13);

                index = s.findID(isbn);
                if (index == -1){
                    printf("There is no book with the ISBN: %s!\n", isbn);
                }else{
                    s.books[index].display();
                    system("PAUSE");
                }
                break;
            case '6':
                system("CLS");
                s_input("Name of book you want to find: ", name, 16);

                index = s.findName(name);
                if (index == -1){
                    printf("There is no book with the name: %s!\n", name);
                }else{
                    s.books[index].display();
                    system("PAUSE");
                }
                break;
            default:
                break;
		}
	}
}

void readersPage(ListReader &r){
    //ev is code of key press event in ascii
    int ev = 0;

    //27 is escape key
    //Main loop repeats until user press ESC
    while (ev != 27)
	{
		system("CLS");
		printf("******Reader section******\n");
		printf("* 1. Add new reader      *\n");
		printf("* 2. Display readers     *\n");
		printf("* 3. Edit reader         *\n");
		printf("* 4. Delete reader       *\n");
		printf("* 5. Find reader by ID   *\n");
		printf("* 6. Find reader by name *\n");
		printf("* ESC. Exit              *\n");
		printf("**************************");
		ev = _getch();

        char id[14], name[16];
        int index;

		switch (ev){
            case '1':
                r.add();
                break;
            case '2':
                r.display();
                break;
            case '3':
                system("CLS");
                s_input("ID of reader you want to edit: ", id, 13);

                index = r.findID(id);
                if (index == -1){
                    printf("There is no reader with the ID: %s!\n", id);
                }else{
                    r.readers[index].edit();
                }
                break;
            case '4':
                system("CLS");
                s_input("ID of reader you want to delete: ", id, 13);

                index = r.findID(id);
                if (index == -1){
                    printf("There is no reader with the DI: %s!\n", id);
                }else{
                    r.remove(index);
                    printf("Reader deleted!\n");
                    Sleep(1000);
                }
                break;
            case '5':
                system("CLS");
                s_input("ID of reader you want to find: ", id, 13);

                index = r.findID(id);
                if (index == -1){
                    printf("There is no reader with the ID: %s!\n", id);
                }else{
                    r.readers[index].display();
                    system("PAUSE");
                }
                break;
            case '6':
                system("CLS");
                s_input("Name of reader you want to find: ", name, 16);

                index = r.findName(name);
                if (index == -1){
                    printf("There is no reader with the name: %s!\n", name);
                }else{
                    r.readers[index].display();
                    system("PAUSE");
                }
                break;
            default:
                break;
		}
	}
}

void cardsPage(Stock &s, ListReader &r, ListCard lc){
    //ev is code of key press event in ascii
    int ev = 0;

    //27 is escape key
    //Main loop repeats until user press ESC
    while (ev != 27)
	{
		system("CLS");
		printf("***Card section***\n");
		printf("* 1. Borrow book *\n");
		printf("* 2. Return book *\n");
		printf("* ESC. Exit      *\n");
		printf("******************");
		ev = _getch();

		switch (ev){
            case '1':
                lc.add(s, r);
                break;
            case '2':
                lc.returning(s, r);
                break;
            default:
                break;
		}
	}
}

//Main function is responsible for print main menu and navigate to smaller section
int main(){
    //check if user have the account to use
    if (!SignedIn()) return 0;

    //ev is code of key press event in ascii
    int ev = 0;

    Stock stock;
    ListReader readers;

    //Load old data
    stock.load();
    readers.load();

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
                booksPage(stock);
                break;
            case '2':
                readersPage(readers);
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