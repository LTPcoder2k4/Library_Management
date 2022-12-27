#include "Books.h"
#include "Handle.h"
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <cstring>

void Book::operator = (const Book book){
    memcpy(this->isbn, (char *) book.isbn, strlen(book.isbn) + 1);
    memcpy(this->name, (char *) book.name, strlen(book.name) + 1);
    memcpy(this->author, (char *) book.author, strlen(book.author) + 1);
    memcpy(this->publisher, (char *) book.publisher, strlen(book.publisher) + 1);
    memcpy(this->category, (char *) book.category, strlen(book.category) + 1);
    memcpy(this->price, (char *) book.price, strlen(book.price) + 1);
    this->publishDate = book.publishDate;
    this->isBorrow = book.isBorrow;
}

void Book::create(){
    s_input("Book's ISBN: ", this->isbn, 13);
    s_input("Book's name: ", this->name, 16);
    s_input("Book's author: ", this->author, 16);
    s_input("Book's publisher: ", this->publisher, 16);
    printf("Book's publish date:\n"); this->publishDate.create();
    s_input("Book's category: ", this->category, 17);
    s_input("Book's price: ", this->price, 17);
}

void Book::display(){
    printf("%14s|%17s|%17s|%17s|%11s|%17s|%17s|\n", 
    this->isbn, this->name, this->author, 
    this->publisher, this->publishDate.toString(), this->category, this->price);
}

void Book::edit(){
    //ev is code of key press event in ascii
    int ev = 0;

    //27 is escape key
    //Main loop repeats until user press ESC
    while (ev != 27)
	{
		system("CLS");
		printf("****Book editing***\n");
		printf("* 1. Name         *\n");
		printf("* 2. Author       *\n");
		printf("* 3. Publisher    *\n");
		printf("* 4. Publish date *\n");
		printf("* 5. Category     *\n");
		printf("* 6. Price        *\n");
		printf("* ESC. Exit       *\n");
		printf("*******************");
		ev = _getch();

        char field[100];
        Date newDate;
        int index;

        system("CLS");

		switch (ev){
            case '1':
                s_input("Enter new name: ", field, 16);
                memcpy(this->name, field, strlen(field));
                break;
            case '2':
                s_input("Enter new author: ", field, 16);
                memcpy(this->author, field, strlen(field));
                break;
            case '3':
                s_input("Enter new publisher: ", field, 16);
                memcpy(this->publisher, field, strlen(field));
                break;
            case '4':
                printf("Enter new publish date:\n");
                newDate.create();
                this->publishDate = newDate;
                break;
            case '5':
                s_input("Enter new category: ", field, 16);
                memcpy(this->category, field, strlen(field));
                break;
            case '6':
                s_input("Enter new price: ", field, 16);
                memcpy(this->price, field, strlen(field));
                break;
            default:
                break;
		}

        printf("New information is updated!\n");
        Sleep(1000);
	}
}

void Stock::load(){
    FILE *f = fopen(this->fileName, "rb");
    if (f != NULL){
        fscanf(f, "%d\n", &this->bookQuantity);
        for (int i = 0; i < this->bookQuantity; i++){
            fscanf(f, "%[^,],%[^,],%[^,],%[^,],%d/%d/%d,%[^,],%[^,],%d,\n",
                this->books[i].isbn, this->books[i].name, this->books[i].author, 
                this->books[i].publisher, &this->books[i].publishDate.day, 
                &this->books[i].publishDate.month, &this->books[i].publishDate.year, 
                this->books[i].category, this->books[i].price, &this->books[i].isBorrow
            );
        }
        printf("Load stock from file successful!\n");
        fclose(f);
    }else{
        printf("File \"%s\" not found!\n", this->fileName);
        system("PAUSE");
    }
}

void Stock::save(){
    FILE *f = fopen(this->fileName, "wb");
    if (f != NULL){
        fprintf(f, "%d\n", this->bookQuantity);
        for (int i = 0; i < this->bookQuantity; i++){
            fprintf(f, "%s,%s,%s,%s,%s,%s,%s,%d,\n", 
                this->books[i].isbn, this->books[i].name, this->books[i].author, 
                this->books[i].publisher, this->books[i].publishDate.toString(), 
                this->books[i].category, this->books[i].price, this->books[i].isBorrow
            );
        }
        fclose(f);
    }else{
        printf("Cannot create file \"%s\"!\n", this->fileName);
        system("PAUSE");
    }
}

int Stock::findID(char id[]){
    for (int index = 0; index < this->bookQuantity; index++){
        if (isEqual(this->books[index].isbn, id)) return index;
    }

    return -1;
}

int Stock::findName(char name[]){
    for (int index = 0; index < this->bookQuantity; index++){
        if (isEqual(this->books[index].name, name)) return index;
    }

    return -1;
}

void Stock::add(){
    system("CLS");

    //Create new book in last position
    Book temp;
    temp.create();
    //Check if isbn is unique
    if (this->findID(temp.isbn) != -1){
        printf("ISBN %s is already exist!\n", temp.isbn);
    }

    this->books[this->bookQuantity] = temp;
    //Increase number of books when add new successfully
    this->bookQuantity++;

    printf("New book added successfully!\n");
    //Save new data
    this->save();
    system("PAUSE");
}

void Stock::display(){
    system("CLS");

    //Print title of table
	printf("%14s|%17s|%17s|%17s|%11s|%17s|%17s|\n", "ISBN", "Name", "Author", "Publisher", "Publish Day", "Category", "Price");

    //For loop to print each book in stock
    for (int index = 0; index < this->bookQuantity; index++){
        if (!this->books[index].isBorrow){
            this->books[index].display();
        } 
    }

	printf("\n");

    system("PAUSE");
}

//Idea: Remove a book out of stock by pushing it to the end and decrease book's quantity
void Stock::remove(int position){
    this->bookQuantity--;

    for (int index = position; index < this->bookQuantity; index++){
        this->books[index] = this->books[index + 1];
    }
    //Save new data
    this->save();
}