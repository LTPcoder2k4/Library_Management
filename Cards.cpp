#include "Cards.h"
#include "windows.h"
#include "Handle.h"
#include <stdio.h>
#include <cstring>
#include <stdlib.h>

void ListCard::save(){
    FILE* f = fopen(this->fileName, "wb");
    if (f != NULL){
        fprintf(f, "%d\n", this->cardQuantity);
        for (int i = 0; i < this->cardQuantity; i++){
        fprintf(f, "%s,%s,%s,\n",
            this->cards[i].borrowDate.toString(),
            this->cards[i].isbn,
            this->cards[i].id
        );
    }
    }else{
        printf("Cannot create file \"%s\"!\n", this->fileName);
        system("PAUSE");
    }
    fclose(f);
}

void ListCard::load(){
    FILE* f = fopen(this->fileName, "rb");
    if (f != NULL){
        fscanf(f, "%d\n", &this->cardQuantity);
        for (int index = 0; index < this->cardQuantity; index++){
            fscanf(f, "%d/%d/%d,%[^,],%[^,],\n",
                &this->cards[index].borrowDate.day,
                &this->cards[index].borrowDate.month,
                &this->cards[index].borrowDate.year,
                this->cards[index].isbn,
                this->cards[index].id
            );
        }
        printf("Load list of cards from file successful!\n");
        fclose(f);
    }else{
        printf("File \"%s\" not found!\n", this->fileName);
        system("PAUSE");
    }
    
    fclose(f);
}

void ListCard::add(Stock &b, ListReader r){
    system("CLS");

    char isbn[14], id[7];
    Date borrow;

    inputBook:
    s_input("Book's ISBN: ", isbn, 13);

    if (b.findID(isbn) == -1){
        printf("There is no book with ISBN: %s! Try again!\n", isbn);
        goto inputBook;
    }

    inputReader:
    s_input("Reader's ID: ", id, 6);

    if (r.findID(id) == -1){
        printf("There is no reader with ID: %s! Try again!\n", id);
        goto inputReader;
    }

    printf("Borrowing date: \n"); borrow.create();

    //Already taken enough information
    //Push new card to the last
    this->cards[this->cardQuantity].borrowDate = borrow;
    memcpy(this->cards[this->cardQuantity].isbn, isbn, strlen(isbn));
    memcpy(this->cards[this->cardQuantity].id, id, strlen(id));
    this->cardQuantity++;

    //mark the book is borrowed
    b.books[b.findID(isbn)].isBorrow = true;
    //save to file
    this->save();
}

int ListCard::findCard(char isbn[], char id[]){
    for (int index = 0; index < this->cardQuantity; index++){
        if (isEqual(this->cards[index].isbn, isbn) && isEqual(this->cards[index].id, id)){
            return index;
        }
    }

    return -1;
}

void ListCard::returning(Stock &b, ListReader &r){
    system("CLS");

    char isbn[14], id[7];
    Date returningDate;

    inputCard:
    s_input("Book's ISBN: ", isbn, 13);
    s_input("Reader's ID: ", id, 6);

    if (this->findCard(isbn, id) == -1){
        printf("There is no matching information card!\n");
        goto inputCard;
    }

    bool isDisappear;
    printf("If the book is disappear, enter 1, otherwise 0: "); scanf("%d", &isDisappear);

    if (isDisappear){
        printf("Oh no, you have to pay %d!\n", parseInt(b.books[b.findID(isbn)].price) * 2);
        //Delete the disappear book
        b.remove(b.findID(isbn));
    }else{
        printf("Enter the returning date: \n"); returningDate.create();
        //Increase the borrowing day a week to take the time different
        this->cards[this->findCard(isbn, id)].borrowDate.aWeekAfter();
        //Calculate the time different
        int day = this->cards[this->findCard(isbn, id)].borrowDate - returningDate;
        if (day < 0){
            printf("You have to pay %d for penalty!\n", day * 5000 * -1);
            //Mark user as late returning
            r.readers[r.findID(id)].isLateReturning = true;
        }else{
            printf("Huray! return on time!\n");
        }

        //Mark book as returned
        b.books[b.findID(isbn)].isBorrow = false;
    }
    //Delete card
    this->remove(this->findCard(isbn, id));
    system("PAUSE");
}

void ListCard::remove(int position){
    this->cardQuantity--;

    for (int index = position; index < this->cardQuantity; index++){
        this->cards[index] = this->cards[index + 1];
    }

    //Save new data
    this->save();
}