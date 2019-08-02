#ifndef VIGENERE_H
#define VIGENERE_H

#include "frase.h"
#include <QWidget>

class Vigenere: public Frase{
private:
    string Key; //Chiave
    int S[200]; //array per numero di spostamenti
    char Risultato[200]; //Testo risultante
    char CipherString[200]; //Stringa di cifratura
public:
    Vigenere(string k="",string p="");
    void buildStringVig();
    void codifica();
    void codificaRev();
    char* getRisultato() const;
    char* getCipherString() const;
    string getKey() const;
    char getLetteraRev(char,int) const;
};

#endif // VIGENERE_H
