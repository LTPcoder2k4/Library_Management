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

    //description: save list of card to local file
    void save();

    //description: load list of card from local file
    void load();
    
    //description: take new card data from user and mark a book as isBorrowed when sucess
    //parameter 1: stock where store list of books
    //parameter 2: ListReader where store list of readers
    void add(Stock&, ListReader);

    //description: return the position of the card meeting the criteria
    //parameter 1: isbn of book that needed to be compared
    //parameter 2: id of reader that needed to be compared
    int findCard(char[], char[]);

    //description: take borrowing card data from user and unmark a book from isBorrowed when sucess or remove it when it is disappeared
    //parameter 1: stock where store list of books
    //parameter 2: ListReader where store list of readers
    void returning(Stock&, ListReader&);

    //description: remove a card out of list with the given position
    //parameter: card position that needed to be removed
    void remove(int);
};

#endif