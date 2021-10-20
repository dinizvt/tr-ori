#include <iostream>
#include <stdio.h>
#include <fstream>

#include "arquivo.h"
#include "pessoa.h"

using namespace std;

void writeUntilStop (Arquivo* f) {
    Pessoa* p;
    do {
        p = inputRecord();
        if (p != NULL) f->add(p);
        else break;
    } while (p != NULL);
}

int main (int argc, char** argv) {
    Arquivo* f = new Arquivo("teste");
    writeUntilStop(f);
    f->rm(2);
    f->readByKey(2);
}