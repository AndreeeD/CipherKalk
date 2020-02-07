#include <QWidget>
#include "frase.h"
#include <QMessageBox>
#include <iostream>
#include <string>


/* Effuttuo i controlli per vedere se la frase rispetta i vincoli(ovvero se è costituita da soli caratteri alfabetici e spazi)
 e in caso affermativo trasformo ogni lettera da minuscolo a maiuscolo, ignorando gli spazi */
Frase::Frase(string p): Phrase(p){
        int nspazi = 0;
        int a = Phrase.length();
        for(int i=0;i<a;i++){
            if(Phrase.at(i) == ' ') nspazi++;
        }
        if(nspazi == a){
            warning("La frase non può contenere solo spazi!");
            Phrase = "";
        }
        else{
            bool s = true;
            for(int i=0;i<a && s;i++){
                if((Phrase.at(i)>='a' && Phrase.at(i)<='z') || (Phrase.at(i)>='A' && Phrase.at(i)<='Z') || Phrase.at(i) == ' '){
                    if(Phrase.at(i) == ' ') Phrase.at(i) = ' ';
                    else Phrase.at(i) = toupper(Phrase.at(i));
                }
                else{
                    warning("La frase deve contenere solo caratteri alfabetici e spazi!");
                    Phrase = "";
                    s = false;
                }
            }
        }
    }
/* Trovo e ritorno la lettera che si trova 'pos' posizioni dopo rispetto a 'c' */
char Frase::getLettera(char c,int pos) const{
    char l;
    int temp=0;
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
    char* t = new char[27];
    strcpy(t,Alfa);
    return t;
}
/* Lancio un messaggio di errore 's' su una nuova finestra */
void Frase::warning(const QString& s){
    QMessageBox* msgBox = new QMessageBox();
    msgBox->setText(s);
    msgBox->setWindowTitle("ERRORE");
    msgBox->exec();
}
/* Inizializzazione della variabile statica */
char Frase::Alfa[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
