#include "arquivo.h"

using namespace std;

Arquivo::Arquivo(string filename)
{
    this->filename = filename;
    this->file.open(filename, ios::binary | ios::in | ios::out | ios::app);
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
    for (int i=0; file.good(); i++) {
        printf("%d\n",i);
        file.seekg(sizeof(Header) + i*sizeof(Pessoa), ios::beg);
        if (file.peek() == key) {
            return file.tellg();
        }
    }
    return -1;
}

void Arquivo::add (Pessoa* record) {
    cout << file.fail() << endl;
    int pos = this->findKey(record->key);
    if (pos != -1) {
        cout << "CHAVE JA EXISTE\n";
        return;
    }
    if (this->header.firstAv == -1) {
        file.seekp(0,ios::end);
        file.write((char *) (record), sizeof(Pessoa));
        file.flush(); 
    }
    else {
        int fa = this->header.firstAv;
        int fa_pos = sizeof(Header)+fa*sizeof(Pessoa);
        int na;
        file.seekg(fa_pos+1, ios::beg);
        file.read((char*) &na, sizeof(int));
        this->header.firstAv = na;
        file.seekp(fa_pos, ios::beg);
        file.write((char *) (record), sizeof(Pessoa));
        file.flush(); 
    }
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