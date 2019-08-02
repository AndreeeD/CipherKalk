#ifndef FRASE_H
#define FRASE_H

#include <QWidget>
using namespace std;

class Frase{
private:
    string Phrase; //Testo inserito
    static char Alfa[26]; //Lettere dell'alfabeto in maiuscolo
public:
    Frase(string p);
    virtual ~Frase() {}
    virtual void codifica() =0;
    virtual char* getRisultato() const=0;
    char getLettera(char c,int pos) const;
    string getPhrase() const;
    char* getAlfa() const;
    static void warning(const QString& s);
};

#endif // FRASE_H
