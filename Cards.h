#ifndef CARDS_H
#define CARDS_H

#include "Books.h"
#include "Readers.h"
#include "Date.h"

struct Card{
    char isbn[14];
    char id[7];
    Date borrowDate;
};

struct ListCard{
    int cardQuantity = 0;
    Card cards[100];
    const char* fileName = "cards.csv";

    void save();
    void load();
    void add(Stock&, ListReader);
    int findCard(char[], char[]);
    void returning(Stock&, ListReader&);
    void remove(int);
};

#endif