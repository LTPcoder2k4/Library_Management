#ifndef BOOK_H
#define BOOK_H

struct Book{
    char id[7],
        name[17],
        author[17],
        publisher[17],
        publishDate[11],
        category[17],
        price[17];

    bool isBorrow = false;

    void operator = (const Book&);
    void create();
};

struct Stock{
    int bookQuantity = 0;
    Book books[100];

    void addBook();
};

#endif