#ifndef SOSTITUZIONE_H
#define SOSTITUZIONE_H

#include "frase.h"
#include <QWidget>

class Sostituzione: public Frase{
private:
    char Risultato[200]; //Testo cifrato
    int N; //Numero di spostamenti
public:
    Sostituzione(int n=0,string p="");
    void codifica();
    char* getRisultato() const;
};

#endif // SOSTITUZIONE_H
