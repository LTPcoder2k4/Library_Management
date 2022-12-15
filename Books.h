#ifndef BOOK_H
#define BOOK_H

#include "Date.h"

struct Book{
    char id[7],
        isbn[14],
        name[17],
        author[17],
        publisher[17],
        category[17],
        price[17];

    Date publishDate;

    bool isBorrow = false;

    void operator = (const Book);
    void create();
    void display();
};

struct Stock{
    int bookQuantity = 0;
    Book books[100];
    const char* fileName = "Stock.json";

    void push();
    void pull();
    int findID(char[]);
    int findName(char[]);
    void add();
    void display();
    void remove(int);
};

#endif