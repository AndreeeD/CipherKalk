#include "vigenere.h"
#include <iostream>
/* Controllo se la chiave inserita rispetta i vincoli imposti (ovvero se è costituita da soli caratteri alfabetici) e in
 * caso affermativo trasformo ogni lettera da minuscolo a maiuscolo */
    Vigenere::Vigenere(string k,string p):Frase(p),Key(k){
        if(Key == "") Frase::warning("Non hai inserito la chiave!");
        else{
            int sizeK = Key.size();
            bool s = true;
            for(int i=0;i<sizeK && s;i++){
                if((Key.at(i)>='a' && Key.at(i)<='z') || (Key.at(i)>='A' && Key.at(i)<='Z')){
                    Key.at(i) = toupper(Key.at(i));
                }
                else{
                    Frase::warning("La chiave deve contenere solo caratteri alfabetici senza spazi!");
                    Key = "";
                    s = false;
                }
            }
        }
    }
/* Cifro il testo in chiaro */
    void Vigenere::codifica() {
        buildStringVig();
        string f = getPhrase();
        int sizeF = f.size();
        for(int i=0;i<sizeF;i++){
            if(S[i] != 0)
                Risultato[i] = getLettera(f.at(i),S[i]);
            else Risultato[i] = f.at(i);
        }
    }
/* Decifro il testo cifrato */
    void Vigenere::codificaRev() {
        buildStringVig();
        string f = getPhrase();
        int sizeF = f.size();
        for(int i=0;i<sizeF;i++){
            if(S[i] != 0)
                Risultato[i] = getLetteraRev(f.at(i),S[i]);
            else Risultato[i] = f.at(i);
        }
    }
/* Costruisco la stringa di cifratura e l'array che conterrà il numero di spostamenti da effettuare per ciascuna lettera
   del testo inserito */
    void Vigenere::buildStringVig(){
        string f = getPhrase();
        char* Lett = getAlfa();
        int sizeF = f.size();
        int sizeK = Key.size();
        for(int i=0,j=0;i<sizeF;i++){
            if(f.at(i)!=' '){
                if(j>=sizeK) j=0;
                CipherString[i] = Key.at(j);
                j++;
            }
            else CipherString[i] = ' ';
        }
        for(int i=0;i<sizeF;i++){
            if(CipherString[i]!=' '){
                for(int j=0;j<26;j++){
                    if(CipherString[i] == Lett[j]) S[i] = j;
                }
            }
            else S[i] = 0;
        }
    }
/* Trovo e ritorno la lettera che si trova 'pos' posizioni prima rispetto a 'c' */
    char Vigenere::getLetteraRev(char c,int pos) const{
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
/* Ritorno il testo risultante */
    char* Vigenere::getRisultato() const{
        char* p = new char[getPhrase().size()+1];
        strcpy(p,Risultato);
        return p;
    }
/* Ritorno la stringa di cifratura */
    char* Vigenere::getCipherString() const{
        char* p=new char[getPhrase().size()+1];
        strcpy(p,CipherString);
        return p;
    }
/* Ritorno la chiave */
    string Vigenere::getKey() const{ return Key; }
