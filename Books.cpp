#include "Books.h"
#include "Handle.h"
#include <conio.h>
#include <windows.h>

void Book::operator = (const Book &book){
    substring((char *) book.id, this->id);
    substring((char *) book.name, this->name);
    substring((char *) book.author, this->author);
    substring((char *) book.publisher, this->publisher);
    substring((char *) book.publishDate, this->publishDate);
    substring((char *) book.category, this->category);
    substring((char *) book.price, this->price);
}

void Book::create(){
    s_input("Book's name: ", this->name, 16);
    s_input("Book's author: ", this->author, 16);
    s_input("Book's publisher: ", this->publisher, 16);
    s_input("Book's publish date: ", this->publishDate, 11);
    s_input("Book's category: ", this->category, 17);
    s_input("Book's price: ", this->price, 17);
}

void Stock::addBook(){
    system("CLS");
    this->books[this->bookQuantity].create();
    this->bookQuantity++;
}