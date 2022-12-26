#ifndef READERS_H
#define READERS_H

#include "Date.h"

struct Reader{
    char id[7], name[17], identityCard[13], sex[7], email[31], address[31];
    Date birthday, dateCreated, dateExpired;
    bool isLateReturning = false;

    void operator = (const Reader);
    void create();
    void display();
    void edit();
};

struct ListReader{
    int readerQuantity = 0;
    Reader readers[100];
    const char* fileName = "readers.csv";

    void save();
    void load();
    int findID(char[]);
    int findName(char[]);
    void add();
    void display();
    void remove(int);
};

#endif