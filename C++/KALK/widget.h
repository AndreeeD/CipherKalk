#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "sostituzione.h"
#include "vernam.h"
#include "vigenere.h"
#include "frase.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
private:
    Frase* F;
    QList<QWidget*> Qw; //Array che contiene tutti i Widget creati
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    //Metodi per cifrare
    void withSostituzione();
    void withVigenere();
    void withVernam();
    //Metodi per decifrare
    void withVigenereRev();
    void withVernamRev();
private slots:
    void on_cifra_clicked();
    void on_decifra_clicked();
    void on_reset_clicked();
    //Metodi per disabilitare bottoni e campi del Widget GroupBox
    void disableButton23();
    void disableButton12();
    void disableButton13();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
