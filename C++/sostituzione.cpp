#include "sostituzione.h"
#include <iostream>
/* Controllo se 'n' è corretto */
    Sostituzione::Sostituzione(int n,string p):Frase(p),N(n){
        if(n<0 || n>26) Frase::warning("Il numero di spostamenti deve essere dentro il range 0-26!");
    }
/* Costruisco il testo cifrato */
    void Sostituzione::codifica() {
        string f = getPhrase();
        for(int i=0;i<f.size();i++){
            if(f.at(i) == ' ') Risultato[i] = ' ';
            else Risultato[i] = getLettera(f.at(i),N);
        }
    }
/* Stampa */
    void Sostituzione::stampa() const{
        cout<<"Frase codificata usando la sostituzione: ";
        for(int i=0;i<getPhrase().size();i++) cout<<Risultato[i];
        cout<<endl;
    }
/* Ritorno il testo cifrato */
    char* Sostituzione::getRisultato() const{
        char* p = new char[getPhrase().size()];
        strcpy(p,Risultato);
        return p;
    }
