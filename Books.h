#ifndef BOOK_H
#define BOOK_H

#include "Date.h"

struct Book{
    char isbn[14],
        name[17],
        author[17],
        publisher[17],
        category[17],
        price[17];

    Date publishDate;

    bool isBorrow = false;

    //description: overload operator equal to copy other Book variable to this variable
    //parameter: book that is used to copy its data
    void operator = (const Book);

    //description: take date data from user
    void create();

    //description: display fields of this object
    void display();

    //description: take new date data from user and save it to this object
    void edit();
};

struct Stock{
    int bookQuantity = 0;
    Book books[100];
    const char* fileName = "books.csv";

    //description: save list of book to local file
    void save();

    //description: load list of book from local file
    void load();

    //description: return the position of the book meeting the criteria
    //parameter: isbn that needed to be compared
    int findID(char[]);

    //description: return the position of the book meeting the criteria
    //parameter: name that needed to be compared  
    int findName(char[]);

    //description: take new book data from user
    void add();

    //description: display fields of list of book object
    void display();

    //description: remove the book out of stock
    //parameter: position of book needed to be removed
    void remove(int);
};

#endif