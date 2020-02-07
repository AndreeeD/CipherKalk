#include "frase.h"
#include <QMessageBox>
#include <iostream>

/* Effuttuo i controlli per vedere se la frase rispetta i vincoli(ovvero se è costituita da soli caratteri alfabetici e spazi)
 e in caso affermativo trasformo ogni lettera da minuscolo a maiuscolo, ignorando gli spazi */
Frase::Frase(string p): Phrase(p){
        int nspazi = 0;
        for(int i=0;i<Phrase.size();i++){
            if(Phrase.at(i) == ' ') nspazi++;
        }
        if(nspazi == Phrase.size()){
            warning("La frase non può contenere solo spazi!");
            Phrase = "";
        }
        else{
            for(int i=0;i<Phrase.size();i++){
                if((Phrase.at(i)>='a' && Phrase.at(i)<='z') || (Phrase.at(i)>='A' && Phrase.at(i)<='Z') || Phrase.at(i) == ' '){
                    if(Phrase.at(i) == ' ') Phrase.at(i) = ' ';
                    else Phrase.at(i) = toupper(Phrase.at(i));
                }
                else{
                    warning("La frase deve contenere solo caratteri alfabetici e spazi!");
                    Phrase = "";
                    break;
                }
            }
        }
    }
/* Trovo e ritorno la lettera che si trova 'pos' posizioni dopo rispetto a 'c' */
char Frase::getLettera(char c,int pos) const{
    char l;
    int temp;
    for(int i=0;i<26;i++){

        if(Alfa[i]==c){
            temp = i;
            break;
        }
    }
    if(25-temp >= pos) l = Alfa[temp+pos];
    else{
        pos = pos - (25-temp) -1;
        l = Alfa[pos];
    }
    return l;
}
/* Ritorno la frase inserita */
string Frase::getPhrase() const{ return Phrase; }
/* Ritorno l'elenco delle lettere dell'alfabeto */
char* Frase::getAlfa() const{
    char* t = new char[26];
    strcpy(t,Alfa);
    return t;
}
/* Stampo la frase */
void Frase::stampa() const{
    cout<<"Frase in chiaro: "<<Phrase<<endl;
}
/* Lancio un messaggio di errore 's' su una nuova finestra */
void Frase::warning(const QString& s){
    QMessageBox msgBox;
    msgBox.setText(s);
    msgBox.setWindowTitle("ERRORE");
    msgBox.exec();
}
/* Inizializzazione della variabile statica */
char Frase::Alfa[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
