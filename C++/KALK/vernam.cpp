#include "vernam.h"
#include <iostream>
/* Controllo se la chiave inserita rispetta i vincoli imposti (ovvero se è costituita da soli caratteri alfabetici ed ha una
 * lunghezza uguale a quella del testo inserito) e in caso affermativo trasformo ogni lettera da minuscolo a maiuscolo */
   Vernam::Vernam(string k,string p):Frase(p),Key(k){
       if(Key == "") Frase::warning("Non hai inserito la chiave!");
       else{
           int nSpazi=0;
           int sizeF = p.size();
           int sizeK = Key.size();
           for(int i=0;i<sizeF;i++)
               if(p.at(i) == ' ') nSpazi++;
           if(sizeK != sizeF-nSpazi){
               Frase::warning("Chiave e frase hanno lunghezza diversa!");
               Key="";
           }
           else{
               bool s = true;
               for(int i=0;i<sizeK && s;i++){
                   if((Key.at(i)>='a' && Key.at(i)<='z') || (Key.at(i)>='A' && Key.at(i)<='Z')){
                       Key.at(i) = toupper(Key.at(i));
                   }
                   else{
                       Frase::warning("La chiave deve contenere solo caratteri alfabetici senza spazi!");
                       Key="";
                       s = false;
                   }
               }
           }
       }
    }
/* Cifro il testo in chiaro */
    void Vernam::codifica() {
        buildStringVe();
        string f = getPhrase();
        int sizeF = f.size();
        for(int i=0,j=0;i<sizeF;i++){
            if(f.at(i)==' ') Risultato[i] = ' ';
            else{
                Risultato[i] = getLettera(f.at(i),S[j]);
                j++;
            }
        }
    }
/* Decifro il testo cifrato */
    void Vernam::codificaRev() {
        buildStringVe();
        string f = getPhrase();
        int sizeF = f.size();
        for(int i=0,j=0;i<sizeF;i++){
            if(f.at(i)==' ') Risultato[i] = ' ';
            else{
                Risultato[i] = getLetteraRev(f.at(i),S[j]);
                j++;
            }
        }
    }
/* Costruisco la stringa di cifratura e l'array che conterrà il numero di spostamenti da effettuare per ciascuna lettera
   del testo inserito */
    void Vernam::buildStringVe(){
        string f = getPhrase();
        char* Lett = Frase::getAlfa();
        int sizeF = f.size();
        for(int i=0,j=0;i<sizeF;i++){
            if(f.at(i) == ' ') CipherString[i] = ' ';
            else{
                CipherString[i] = Key.at(j);
                j++;
            }
        }
        int sizeK = Key.size();
        for(int i=0;i<sizeK;i++){
            for(int j=0;j<26;j++){
                if(Key.at(i) == Lett[j]) S[i] = j;
            }
        }
    }
/* Trovo e ritorno la lettera che si trova 'pos' posizioni prima rispetto a 'c' */
    char Vernam::getLetteraRev(char c,int pos) const{
        char l;
        char* alfa = getAlfa();
        int temp=0;
        for(int i=0;i<26;i++){
            if(alfa[i]==c){
                temp = i;
                break;
            }
        }
        if(temp >= pos)
            l = alfa[temp-pos];
        else{
            pos = 26 + (temp-pos);
            l = alfa[pos];
        }
        return l;
    }
/* Ritorno il testo risultante */
    char* Vernam::getRisultato() const{
        char* p = new char[getPhrase().size()+1];
        strcpy(p,Risultato);
        return p;
    }
/* Ritorno la stringa di cifratura */
    char* Vernam::getCipherString() const{
        char* p=new char[getPhrase().size()+1];
        strcpy(p,CipherString);
        return p;
    }
/* Ritorno la chiave */
    string Vernam::getKey() const { return Key; }

