#include "arquivo.h"

using namespace std;

Arquivo::Arquivo(string filename)
{
    this->filename = filename;
    this->file.open(filename, ios::binary | ios::in | ios::out | ios::ate); //abre o arquivo para entrada e saida
    this->file.seekg(0, ios::end);  
    if (this->file.tellg() == 0) { //caso o arquivo esteja em branco
        this->header.firstAv = -1;  //inicia o cabecalho como sem posicoes livres
        this->file.write((char*) &this->header, sizeof(Header));
        this->file.flush();
    }
    else { //caso o arquivo ja exista
        this->file.seekg(0, ios::beg);  
        this->file.read((char*) &(this->header), sizeof(Header)); // le o cabecalho
    }
}

Arquivo::~Arquivo()
{
    this->file.close();
}

/**
 * @brief Funcao responsavel por encontrar a posicao 
 * do item no arquivo de acordo com sua chave
 * 
 * @param key chave do item que deseja encontrar
 * @return int posicao em bytes em que o item se encontra
 */
int Arquivo::findKey (int key) {
    file.seekg(0,ios::beg);
    int pos = -1;
    for (int i=0; file.good() && pos == -1; i++) { //para cada record no arquivo
        file.seekg(sizeof(Header) + i*sizeof(Pessoa), ios::beg);
        if (file.peek() == key) { // caso a key seja a desejada
            pos = file.tellg(); //encerra o loop
        }
    }
    file.seekg(0,ios::beg);
    return pos;
}

/**
 * @brief adiciona um item novo ao arquivo
 * 
 * @param record item a ser adicionado
 */
void Arquivo::add (Pessoa* record) {
    int pos = this->findKey(record->key);
    if (pos != -1) { //verifica existencia da chave
        cout << "CHAVE JA EXISTE\n";
        return;
    }
    if (this->header.firstAv == -1) { // caso nao tenha espaco vago insere no final
        file.seekp(0,ios::end);
        file.write((char *) record, sizeof(Pessoa));
        file.flush(); 
    }
    else { //caso tenha insere no espaco vago
        int fa = this->header.firstAv*sizeof(Pessoa)+sizeof(Header); //primeira posicao livre
        int fa_new; //proxima posicao livre
        file.seekg(fa+1,ios::beg);
        file.read((char*) &fa_new, sizeof(int));
        file.seekg(0,ios::beg);
        file.seekp(fa, ios::beg);
        file.write((char *) record, sizeof(Pessoa));
        file.seekp(0,ios::beg);
        this->header.firstAv = fa_new;
        file.write((char*) &(this->header), sizeof(Header));
        file.flush();
    }
}

/**
 * @brief encontra um record a partir de sua chave
 * 
 * @param key chave a ser buscada
 * @return Pessoa* record encontrado
 */
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

/**
 * @brief lê um arquivo por ordem de cadastro
 * 
 * @param n ordem de cadastro desejada
 * @return Pessoa* record correspondente
 */
Pessoa* Arquivo::readByN (int n) {
    file.seekg (sizeof(Header)+sizeof(Pessoa)*n, ios::beg);
    if (file.eof()) return NULL;
    Pessoa* record = new Pessoa;
    file.read ((char *) record, sizeof(Pessoa));
    return record;
}

/**
 * @brief faz a remocao logica de um record
 * o cabecalho passa a apontar para a posicao removida
 * e a posicao removida passa a apontar pasa a antiga primeira posicao vaga
 * 
 * @param key chave do record a ser removido
 */
void Arquivo::rm (int key) { 
    int pos = findKey(key);
    int n = (pos-sizeof(Header))/sizeof(Pessoa);
    if (pos == -1) return;
    file.seekg(pos);
    this->file.write("*",1); //escreve o asterisco + a proxima posicao vaga no item a ser removido
    this->file.write((char*) &(this->header.firstAv), sizeof(int));
    file.flush();
    file.seekp(0);
    this->header.firstAv = n; //faz o cabecalho apontar para a posicao do item removido
    this->file.write((char*) &(this->header), sizeof(Header));
    this->file.flush();
}