#include "sostituzione.h"
#include <iostream>
/* Controllo se 'n' è corretto */
    Sostituzione::Sostituzione(int n,string p):Frase(p),N(n){
        if(n<0 || n>26) Frase::warning("Il numero di spostamenti deve essere dentro il range 0-26!");
    }
/* Costruisco il testo cifrato */
    void Sostituzione::codifica() {
        string f = getPhrase();
        int sizeF = f.size();
        for(int i=0;i<sizeF;i++){
            if(f.at(i) == ' ') Risultato[i] = ' ';
            else Risultato[i] = getLettera(f.at(i),N);
        }
    }
/* Ritorno il testo cifrato */
    char* Sostituzione::getRisultato() const{
        char* p = new char[getPhrase().size()+1];
        strcpy(p,Risultato);
        return p;
    }

