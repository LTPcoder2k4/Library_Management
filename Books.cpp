#include "Books.h"
#include "Handle.h"
#include <conio.h>
#include <windows.h>
#include <stdio.h>

void Book::operator = (const Book book){
    substring((char *) book.id, this->id);
    substring((char *) book.name, this->name);
    substring((char *) book.author, this->author);
    substring((char *) book.publisher, this->publisher);
    substring((char *) book.category, this->category);
    substring((char *) book.price, this->price);
    this->publishDate = book.publishDate;
}

void Book::create(){
    s_input("Book's name: ", this->name, 16);
    s_input("Book's ISBN: ", this->isbn, 14);
    s_input("Book's author: ", this->author, 16);
    s_input("Book's publisher: ", this->publisher, 16);
    printf("Book's publish date:\n"); this->publishDate.create();
    s_input("Book's category: ", this->category, 17);
    s_input("Book's price: ", this->price, 17);
}

//An ID is valid when it is not appear in the stock
//It will return true if there is no matching id
//Otherwise, it will return false if the id occur in list of book
bool Stock::isValidID(char id[]){
    for (int index = 0; index < this->bookQuantity; index++){
        if (isEqual(this->books[index].id, id)) return false;
    }

    return true;
}

void Stock::addBook(){
    system("CLS");

    //Create new book in last position
    this->books[this->bookQuantity].create();

    //Generally, we can generate id base on its position in stock
    //However, when a book, which is not at last, is deleted
    //The position have some problem when the book after move to previous
    //The loop is make to find the empty position for this situation
    for (int position = this->bookQuantity; position >= 0; position--){
        //Create temporary id
        char id[7] = {'B', '-'};

        //Generate id base on its position in stock
        idGeneration(position, id);

        //Check if the id is unique key
        if (this->isValidID(id)){
            //Assign end of string to last id character
            id[6] = '\0';

            //Copy temporary id to book's id
            substring(id, this->books[this->bookQuantity].id);
            break;
        }
    }

    //Increase number of books when add new successfully
    this->bookQuantity++;
}