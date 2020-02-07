#include "vernam.h"
#include <iostream>
/* Controllo se la chiave inserita rispetta i vincoli imposti (ovvero se è costituita da soli caratteri alfabetici ed ha una
 * lunghezza uguale a quella del testo inserito) e in caso affermativo trasformo ogni lettera da minuscolo a maiuscolo */
   Vernam::Vernam(string k,string p):Frase(p),Key(k){
       if(Key == "") Frase::warning("Non hai inserito la chiave!");
       else{
           int nSpazi=0;
           for(int i=0;i<p.size();i++)
               if(p.at(i) == ' ') nSpazi++;
           if(k.size() != p.size()-nSpazi){
               Frase::warning("Chiave e frase hanno lunghezza diversa!");
               Key="";
           }
           else{
               for(int i=0;i<Key.size();i++){
                   if((Key.at(i)>='a' && Key.at(i)<='z') || (Key.at(i)>='A' && Key.at(i)<='Z')){
                       Key.at(i) = toupper(Key.at(i));
                   }
                   else{
                       Frase::warning("La chiave deve contenere solo caratteri alfabetici senza spazi!");
                       Key="";
                       break;
                   }
               }
           }
       }
    }
/* Cifro il testo in chiaro */
    void Vernam::codifica() {
        buildStringVe();
        string f = getPhrase();
        for(int i=0,j=0;i<f.size();i++){
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
        for(int i=0,j=0;i<f.size();i++){
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
        for(int i=0,j=0;i<f.size();i++){
            if(f.at(i) == ' ') CipherString[i] = ' ';
            else{
                CipherString[i] = Key.at(j);
                j++;
            }
        }
        for(int i=0;i<Key.size();i++){
            for(int j=0;j<26;j++){
                if(Key.at(i) == Lett[j]) S[i] = j;
            }
        }
    }
/* Trovo e ritorno la lettera che si trova 'pos' posizioni prima rispetto a 'c' */
    char Vernam::getLetteraRev(char c,int pos) const{
        char l;
        char* alfa = getAlfa();
        int temp;
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
/* Stampa */
    void Vernam::stampa() const{
        //Frase::stampa();
        cout<<"Frase cifrata con Vernam: ";
        for(int i=0;i<getPhrase().size();i++) cout<<Risultato[i];
    }
/* Ritorno il testo risultante */
    char* Vernam::getRisultato() const{
        char* p = new char[getPhrase().size()];
        strcpy(p,Risultato);
        return p;
    }
/* Ritorno la stringa di cifratura */
    char* Vernam::getCipherString() const{
        char* p=new char[getPhrase().size()];
        strcpy(p,CipherString);
        return p;
    }
/* Ritorno la chiave */
    string Vernam::getKey() const { return Key; }
