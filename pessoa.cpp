#include "pessoa.h"

/**
 * @brief 
 * 
 * @return Pessoa* 
 */
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
    cin.getline(record->firstname, FIRSTNAME_SIZE);
    cout << "Insira o sobrenome\n";
    cin.getline(record->lastname, LASTNAME_SIZE);
    cout << "Insira o endereco\n";
    cin.getline(record->address, ADDRESS_SIZE);
    cout << "Insira a cidade\n";
    cin.getline(record->city, CITY_SIZE);
    cout << "Insira o estado\n";
    cin.getline(record->state, STATE_SIZE);
    cout << "Insira o cep\n";
    cin.getline(record->zip, ZIP_SIZE);
    cout << "Insira o telefone\n";
    cin.getline(record->phone, PHONE_SIZE);
    return record;
}

void printRecord (Pessoa* record) {
    cout << "********************\n";
    printf ("Key: %d\n", record->key);
    printf ("Name: %s %s\n", record->firstname, record->lastname);
    cout << "********************\n";
}
