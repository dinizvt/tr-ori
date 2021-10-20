#include "arquivo.h"

using namespace std;

Arquivo::Arquivo(string filename)
{
    this->filename = filename;
    this->file.open(filename, ios::binary | ios::in | ios::out | ios::ate);
    this->file.seekg(0, ios::end);  
    if (this->file.tellg() == 0) {
        this->header.firstAv = -1;
        this->file.write((char*) &this->header, sizeof(Header));
        this->file.flush();
    }
    else {
        this->file.seekg(0, ios::beg);  
        this->file.read((char*) &(this->header), sizeof(Header));
    }
}

Arquivo::~Arquivo()
{
    this->file.close();
}

int Arquivo::findKey (int key) {
    file.seekg(0,ios::beg);
    int pos = -1;
    for (int i=0; file.good() && pos == -1; i++) {
        file.seekg(sizeof(Header) + i*sizeof(Pessoa), ios::beg);
        if (file.peek() == key) {
            pos = file.tellg();
        }
    }
    file.seekg(0,ios::beg);
    return pos;
}

void Arquivo::add (Pessoa* record) {
    int pos = this->findKey(record->key);
    if (pos != -1) {
        cout << "CHAVE JA EXISTE\n";
        return;
    }
    file.seekp(0,ios::end);
    file.write((char *) record, sizeof(Pessoa));
    file.flush(); 
}

Pessoa* Arquivo::readByKey (int key) {
    int pos = this->findKey(key);
    if (pos == -1) {
        cout << "CHAVE NÃO ENCONTRADA\n";
        return NULL;   
    }
    Pessoa* record = new Pessoa;
    file.seekg(pos, ios::beg);
    file.read ((char *) record, sizeof(Pessoa));
    return record;
}

Pessoa* Arquivo::readByN (int n) {
    file.seekg (sizeof(Header)+sizeof(Pessoa)*n, ios::beg);
    if (file.eof()) return NULL;
    Pessoa* record = new Pessoa;
    file.read ((char *) record, sizeof(Pessoa));
    return record;
}

void Arquivo::rm (int key) {
    int pos = findKey(key);
    int n = (pos-sizeof(Header))/sizeof(Pessoa);
    if (pos == -1) return;
    file.seekg(pos);
    this->file.write("*",1);
    this->file.write((char*) &(this->header.firstAv), sizeof(int));
    file.flush();
    file.seekp(0);
    this->header.firstAv = n;
    this->file.write((char*) &(this->header), sizeof(Header));
    this->file.flush();
}