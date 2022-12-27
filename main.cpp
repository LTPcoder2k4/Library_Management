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

//description: get root username and password from local file
//parameter: username in char[] type is root username
//parameter: password in char[] type is root password
void getAuthorize(char username[], char password[]){
    FILE* f = fopen("user.csv", "rb");
    if (f != NULL){
        fscanf(f, "%[^,],%[^,],\n", username, password);
    }
    fclose(f);
}

//description: Return true if user enter the right username and password
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

//description: mainloop for book section and navigate to action
//parameter: s in Stock type is a list of books
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
                    system("PAUSE");
                }else{
                    s.books[index].edit();
                    s.save();
                }
                break;
            case '4':
                system("CLS");
                s_input("ISBN of book you want to delete: ", isbn, 13);

                index = s.findID(isbn);
                if (index == -1){
                    printf("There is no book with the ISBN: %s!\n", isbn);
                    system("PAUSE");
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
                    system("PAUSE");
                }else{
                    s.books[index].display();
                }
                system("PAUSE");
                break;
            case '6':
                system("CLS");
                s_input("Name of book you want to find: ", name, 16);

                index = s.findName(name);
                if (index == -1){
                    printf("There is no book with the name: %s!\n", name);
                }else{
                    s.books[index].display();
                }
                system("PAUSE");
                break;
            default:
                break;
		}
	}
}

//description: mainloop for reader section and navigate to action
//parameter: r in ListReader type is a list of readers
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
                    r.save();
                }
                break;
            case '4':
                system("CLS");
                s_input("ID of reader you want to delete: ", id, 13);

                index = r.findID(id);
                if (index == -1){
                    printf("There is no reader with the DI: %s!\n", id);
                    system("PAUSE");
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
                    system("PAUSE");
                }else{
                    r.readers[index].display();
                }
                system("PAUSE");
                break;
            case '6':
                system("CLS");
                s_input("Name of reader you want to find: ", name, 16);

                index = r.findName(name);
                if (index == -1){
                    printf("There is no reader with the name: %s!\n", name);
                    system("PAUSE");
                }else{
                    r.readers[index].display();
                }
                system("PAUSE");
                break;
            default:
                break;
		}
	}
}

//description: mainloop for card section and navigate to action
//parameter: s in Stock type is a list of books
//parameter: r in ListReader type is a list of readers
//parameter: lc in ListCard type is a list of cards 
void cardsPage(Stock &s, ListReader &r, ListCard &lc){
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

//description: check if k is already in a
//parameter: k in char[17] type is a string needed to be checked
//parameter: a in char[][17] type is an array of string used for checking
//parameter: n in int type is the number of element in a
bool isIn(char k[17], char a[][17], int n){
    for (int i = 0; i < n; i++){
        if (isEqual(a[i], k)) return true;
    }
    return false;
}

//description: classify book according to its category
//parameter: s in Stock type is a list of books
void classifyCategory(Stock s){
    char category[100][17];
    int n = 0;

    for (int i = 0; i < s.bookQuantity; i++){
        if (!isIn(s.books[i].category, category, n)){
            memcpy(category[n], s.books[i].category, strlen(s.books[i].category) + 1);
            n++;
        }
    }

    printf("Category:\n");
    for (int i = 0; i < n; i++){
        int total = 0;
        for (int j = 0; j < s.bookQuantity; j++){
            if (isEqual(category[i], s.books[j].category)){
                total++;
            }
        }
        printf("- %s: %d\n", category[i], total);
    }
}

//description: mainloop for statistic section and navigate to action
//parameter: s in Stock type is a list of books
//parameter: r in ListReader type is a list of readers
//parameter: lc in ListCard type is a list of cards 
void statisticPage(Stock s, ListReader r, ListCard lc){
    //ev is code of key press event in ascii
    int ev = 0;

    //27 is escape key
    //Main loop repeats until user press ESC
    while (ev != 27)
	{
		system("CLS");
		printf("*****Statistic section******\n");
		printf("* 1. Book's in library     *\n");
		printf("* 2. Book's category       *\n");
		printf("* 3. Reader's in library   *\n");
		printf("* 4. Reader's sex          *\n");
		printf("* 5. Borrowing book        *\n");
		printf("* 6. Late returning reader *\n");
		printf("* ESC. Exit                *\n");
		printf("****************************");
		ev = _getch();

        int result = 0, result2 = 0;
        system("CLS");
		switch (ev){
            case '1':
                printf("There are %d books in library:\n", s.bookQuantity);
                break;
            case '2':
                classifyCategory(s);
                break;
            case '3':
                printf("There are %d readers in library:\n", r.readerQuantity);
                break;
            case '4':
                for (int i = 0; i < r.readerQuantity; i++){
                    if (isEqual(r.readers[i].sex, (char*)"male")) result++;
                    else result2++;
                }
                printf("There are %d male readers and %d female readers\n", result, result2);
                break;
            case '5':
                printf("There are %d borrowing books:\n", lc.cardQuantity);
                break;
            case '6':
                for (int i = 0; i < r.readerQuantity; i++){
                    if (r.readers[i].isLateReturning) result++;
                }
                printf("There are %d late returning readers:\n", result);
                break;
            default:
                break;
		}
        system("PAUSE");
	}
}

//Main function is responsible for print main menu and navigate to smaller section
int main(){
    //check if user have the account to use
    if (!SignedIn()) return 0;

    setSizeConsole(1300, 700);
    //ev is code of key press event in ascii
    int ev = 0;

    Stock stock;
    ListReader readers;
    ListCard cards;

    //Load old data
    stock.load();
    readers.load();
    cards.load();

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
                cardsPage(stock, readers, cards);
                break;
            case '4':
                statisticPage(stock, readers, cards);
                break;
            default:
                break;
		}
	}
    return 0;
}