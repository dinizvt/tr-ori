#ifndef PESSOA_H
#define PESSOA_H

#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

#define LASTNAME_SIZE 10
#define FIRSTNAME_SIZE 10
#define ADDRESS_SIZE 15
#define CITY_SIZE 15
#define STATE_SIZE 2
#define ZIP_SIZE 9
#define PHONE_SIZE 15

typedef struct pessoa {
    int key;
    char lastname [LASTNAME_SIZE];
    char firstname [FIRSTNAME_SIZE];
    //char address [ADDRESS_SIZE];
    //char city [CITY_SIZE];
    //char state [STATE_SIZE];
    //char zip [ZIP_SIZE];
    //char phone [PHONE_SIZE];
} Pessoa;
Pessoa* inputRecord ();
void printRecord (Pessoa* record);

#endif