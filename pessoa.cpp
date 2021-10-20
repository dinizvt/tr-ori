#include "pessoa.h"

Pessoa* inputRecord () {
    Pessoa* record = new Pessoa;
    cout << "Insira a chave\n";
    cin >> record->key;
    cin.get();
    printf("Chave escolhida: %d\n", record->key);
    if (record->key == -1){
        delete record;
        return NULL;
    }
    cout << "Insira o nome\n";
    cin.getline(record->firstname, 10);
    printf("Nome Escolhido: %s\n", record->firstname);
    cout << "Insira o sobrenome\n";
    cin.getline(record->lastname, 10);
    printf("Sobrenome Escolhido: %s\n", record->lastname);
    return record;
}

void printRecord (Pessoa* record) {
    cout << "********************\n";
    printf ("Key: %d\n", record->key);
    printf ("Name: %s %s\n", record->firstname, record->lastname);
    cout << "********************\n";
}
