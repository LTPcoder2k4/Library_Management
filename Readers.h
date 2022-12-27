#ifndef READERS_H
#define READERS_H

#include "Date.h"

struct Reader{
    char id[7], name[17], identityCard[13], sex[7], email[31], address[31];
    Date birthday;
    Date dateCreated;
    Date dateExpired;
    bool isLateReturning = false;

    //description: overload operator equal to copy other Reader variable to this variable
    //parameter: reader that is used to copy its data
    void operator = (const Reader);

    //description: take date data from user
    void create();

    //description: display fields of this object
    void display();

    //description: take new date data from user and save it to this object
    void edit();
};

struct ListReader{
    int readerQuantity = 0;
    Reader readers[100];
    const char* fileName = "readers.csv";

    //description: save list of reader to local file
    void save();

    //description: load list of reader from local file
    void load();

    //description: return the position of reader meeting the criteria
    //parameter: isbn that needed to be compared
    int findID(char[]);

    //description: return the position of the reader meeting the criteria
    //parameter: name that needed to be compared
    int findName(char[]);

    //description: take new reader data from user
    void add();

    //description: display fields of list of reader object
    void display();

    //description: remove the reader out of list
    //parameter: position of reader needed to be removed
    void remove(int);
};

#endif