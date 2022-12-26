#include "Readers.h"
#include "Handle.h"
#include <cstring>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

void Reader::operator=(const Reader reader){
    memcpy(this->id, reader.id, strlen(reader.id) + 1);
    memcpy(this->name, reader.name, strlen(reader.name) + 1);
    memcpy(this->identityCard, reader.identityCard, strlen(reader.identityCard) + 1);
    memcpy(this->sex, reader.sex, strlen(reader.sex) + 1);
    memcpy(this->email, reader.email, strlen(reader.email) + 1);
    memcpy(this->address, reader.address, strlen(reader.address) + 1);
    this->birthday = reader.birthday;
    this->dateCreated = reader.dateCreated;
    this->dateExpired = reader.dateExpired;
    this->isLateReturning = reader.isLateReturning;
}

void Reader::create(){
    s_input("Reader's name: ", name, 16);
	s_input("Reader's ID card: ", identityCard, 12);
	printf("Reader's birthday: \n"); this->birthday.create();
	s_input("Reader's sex(male or female): ", sex, 6);
	s_input("Reader's email: ", email, 30);
	s_input("Reader's address: ", address, 30);
	printf("Reader's creating date: \n"); this->dateCreated.create();
    this->dateExpired = this->dateCreated;
    this->dateExpired.year += 4;
}

void Reader::display(){
    printf("%7s|", this->id);

	printf("%17s|", this->name);

	printf("%13s|", this->identityCard);

	printf("%11s|", this->birthday.toString());

	printf("%7s|", this->sex);

	printf("%31s|", this->email);

	printf("%31s|", this->address);

	printf("%11s|", this->dateCreated.toString());

	printf("%11s|", this->dateExpired.toString());

	printf("\n");
}

void Reader::edit(){
    //ev is code of key press event in ascii
    int ev = 0;

    //27 is escape key
    //Main loop repeats until user press ESC
    while (ev != 27)
	{
		system("CLS");
		printf("****Book editing****\n");
		printf("* 1. Name          *\n");
		printf("* 2. Identity card *\n");
		printf("* 3. Birth day     *\n");
		printf("* 4. Sex           *\n");
		printf("* 5. Email         *\n");
		printf("* 6. Address       *\n");
		printf("* ESC. Exit        *\n");
		printf("********************");
		ev = _getch();

        char field[100];
        Date newDate;
        int index;

        system("CLS");

		switch (ev){
            case '1':
                s_input("Enter new name: ", field, 16);
                memcpy(this->name, field, strlen(field));
                break;
            case '2':
                s_input("Enter new identity card: ", field, 12);
                memcpy(this->identityCard, field, strlen(field));
                break;
            case '3':
                printf("Enter new birth day:\n");
                newDate.create();
                this->birthday = newDate;
                break;
            case '4':
                s_input("Enter new sex: ", field, 7);
                memcpy(this->sex, field, strlen(field));
                break;
            case '5':
                s_input("Enter new email: ", field, 30);
                memcpy(this->email, field, strlen(field));
                break;
            case '6':
                s_input("Enter new address: ", field, 30);
                memcpy(this->address, field, strlen(field));
                break;
            default:
                break;
		}

        printf("New information is updated!\n");
        Sleep(1000);
	}
}

void ListReader::save(){
    FILE* f = fopen(this->fileName, "wb");
    if (f != NULL){
        fprintf(f, "%d\n", this->readerQuantity);
        for (int index = 0; index < this->readerQuantity; index++){
            fprintf(f, "%s,", this->readers[index].id);

            fprintf(f, "%s,", this->readers[index].name);

            fprintf(f, "%s,", this->readers[index].identityCard);

            fprintf(f, "%s,", this->readers[index].birthday.toString());

            fprintf(f, "%s,", this->readers[index].sex);

            fprintf(f, "%s,", this->readers[index].email);

            fprintf(f, "%s,", this->readers[index].address);

            fprintf(f, "%s,", this->readers[index].dateCreated.toString());

            fprintf(f, "%s,", this->readers[index].dateExpired.toString());

            fprintf(f, "\n");
        }
    }else{
        printf("Cannot create file \"%s\"!\n", this->fileName);
        system("PAUSE");
    }
    fclose(f);
}

void ListReader::load(){
    FILE *f = fopen(this->fileName, "rb");
    if (f != NULL){
        fscanf(f, "%d\n", &this->readerQuantity);
        for (int index = 0; index < this->readerQuantity; index++){
            fscanf(f, "%[^,],%[^,],%[^,],%d/%d/%d,%[^,],%[^,],%[^,],%d/%d/%d,%d/%d/%d,\n",
                this->readers[index].id, this->readers[index].name, this->readers[index].identityCard, 
                &this->readers[index].birthday.day, &this->readers[index].birthday.month, &this->readers[index].birthday.year,
                this->readers[index].sex, this->readers[index].email, this->readers[index].address, 
                &this->readers[index].dateCreated.day, &this->readers[index].dateCreated.month, &this->readers[index].dateCreated.year,
                &this->readers[index].dateExpired.day, &this->readers[index].dateExpired.month, &this->readers[index].dateExpired.year
            );
        }
        printf("Load list of readers from file successful!\n");
        fclose(f);
    }else{
        printf("File \"%s\" not found!\n", this->fileName);
        system("PAUSE");
    }
    fclose(f);
}

int ListReader::findID(char id[]){
    for (int index = 0; index < this->readerQuantity; index++){
        if (isEqual(this->readers[index].id, id)) return index;
    }

    return -1;
}

int ListReader::findName(char name[]){
    for (int index = 0; index < this->readerQuantity; index++){
        if (isEqual(this->readers[index].name, name)) return index;
    }

    return -1;
}

void ListReader::add(){
    system("CLS");

    //Create new reader in last position
    this->readers[this->readerQuantity].create();

    //Generally, we can generate id base on its position in stock
    //However, when a book, which is not at last, is deleted
    //The position have some problem when the book after move to previous
    //The loop is make to find the empty position for this situation
    for (int position = this->readerQuantity; position >= 0; position--){
        //Create temporary id
        char id[7] = {'R', '-'};

        //Generate id base on its position in stock
        idGeneration(position, id);

        //Check if the id is unique key
        if (this->findID(id) == -1){
            //Assign end of string to last id character
            id[6] = '\0';

            //Copy temporary id to book's id
            memcpy(this->readers[this->readerQuantity].id, id, strlen(id));
            break;
        }
    }

    //Increase number of readers when add new successfully
    this->readerQuantity++;

    printf("New reader added successfully!\n");
    //Save new data
    this->save();
    system("PAUSE");
}

void ListReader::display(){
    system("CLS");

    //Print title of table
	printf("%7s|%17s|%13s|%11s|%7s|%31s|%31s|%11s|%11s|\n", 
    "ID", "Name", "ID card", "Birthday", "Sex", "Email", "Address", "Created", "Expired");
    //For loop to print each book in stock
    for (int index = 0; index < this->readerQuantity; index++){
        this->readers[index].display();
    }

	printf("\n");

    system("PAUSE");
}

//Idea: Remove a book out of stock by pushing it to the end and decrease book's quantity
void ListReader::remove(int position){
    this->readerQuantity--;

    for (int index = position; index < this->readerQuantity; index++){
        this->readers[index] = this->readers[index + 1];
    }
    //Save new data
    this->save();
}