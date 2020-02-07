#ifndef VERNAM_H
#define VERNAM_H

#include "frase.h"
#include <QWidget>

class Vernam: public Frase{
private:
    string Key; //Chiave
    int S[200]; //array per numero di spostamenti
    char Risultato[200]; //Testo risultante
    char CipherString[200]; //Stringa di cifratura
public:
    Vernam(string k="",string p="");
    void buildStringVe();
    void stampa() const;
    void codifica();
    void codificaRev();
    char* getRisultato() const;
    char* getCipherString() const;
    string getKey() const;
    char getLetteraRev(char,int) const;
};

#endif // VERNAM_H
