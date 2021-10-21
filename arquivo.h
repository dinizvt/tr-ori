#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <iostream>
#include <stdio.h>
#include <fstream>
#include "pessoa.h"

typedef struct header {
    int firstAv;
} Header;


class Arquivo
// class responsavel por gerenciar inserção remoção e consultas ao arquivo
{
private:
    fstream file; //stream do arquivo
    string filename; //nome do arquivo
    Header header; //cabecalho do arquivo
    int findKey (int key); 
public:
    void add (Pessoa* record);
    void rm (int key);
    Pessoa* readByKey (int key);
    Pessoa* readByN (int n);
    Arquivo(string filename);
    ~Arquivo();
};

#endif