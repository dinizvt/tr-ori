#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
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

void menu(Arquivo *f)
{
    Pessoa* p;
    int key;
    bool loop = true;
    int escolha;
    while(loop)
    {
        system("cls");
        cout << "Escolha o que deseja: " << endl;
        cout << "1-) Inserir pessoas " << endl;
        cout << "2-) Excluir pessoas: " << endl;
        cout << "3-)Procurar por key: " << endl;
        cout << "4-) Procurar por ordem de inseção" << endl;
        cout << "5-)Procurar por nome" << endl;
        cout << "0-) Para sair" << endl;
        cin >> escolha;

        switch (escolha)
        {
        case 1:
            writeUntilStop(f);
            break;
        case 2:
            cout << " qual a key que gostaria de excluir? ";
            cin >> key;
            f->rm(key);
            break;
        
        case 3:
            cout << " qual a key que gostaria de buscar? ";
            cin >> key; 
            p = f->readByKey(key);
            printRecord(p);
            break;
        
        case 4:
            int n;
            cout << " qual a 'ordem de inserção' que gostaria de buscar? ";
            cin >> n; 
            p = f->readByN(n);
            printRecord(p);

            break;
        case 5:
            break;
        
        
        default:
            break;
        }
    }


}

int main (int argc, char** argv) {
    Arquivo* f = new Arquivo("teste");
    menu(f);
    return 0;
}