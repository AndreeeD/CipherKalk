#include "widget.h"
#include "ui_widget.h"
#include <QtWidgets>

Widget::Widget(QWidget *parent) :QWidget(parent){
    setWindowTitle(tr("Cipher Kalk"));
    setFixedSize(400,500);
    QLayout* ql = new QVBoxLayout();
    //Layout Frase da inserire
    QLabel* l =new QLabel(tr("Inserisci il testo da cifrare o decifrare:"));
    ql->addWidget(l);
    QTextEdit* txt = new QTextEdit();
    ql->addWidget(txt);
    //Layout QGroupBox
    QGroupBox* gb = new QGroupBox("Cifrario");
    QRadioButton* r1 = new QRadioButton(tr("Sostituzione"));
    QRadioButton* r2 = new QRadioButton(tr("Vigenère*"));
    QRadioButton* r3 = new QRadioButton(tr("Vernam*"));
    QLabel* lso =new QLabel(tr("N° spostamenti:"));
    QComboBox* qb = new QComboBox();
    //lista di elementi per ComboBox
    QStringList list;
    list << "-" << "0" << "1" << "2" << "3" << "4"
            << "5" << "6" << "7" << "8" << "9" << "10" << "11"
            << "12" << "13" << "14" << "15" << "16" << "17"
            << "18" << "19" << "20" << "21" << "22" << "23"
            << "24" << "25" << "26";
    qb->addItems(list);
    //Etichette "chiave"
    QLabel* lvi =new QLabel(tr("Chiave:   "));
    QLabel* lve =new QLabel(tr(" Chiave:  "));
    //Campi input chiavi
    QLineEdit* l1 = new QLineEdit();
    QLineEdit* l2 = new QLineEdit();
    QHBoxLayout* sos = new QHBoxLayout();
    QHBoxLayout* vig = new QHBoxLayout();
    QHBoxLayout* ver = new QHBoxLayout();
    QVBoxLayout* vb = new QVBoxLayout();
    sos->addWidget(r1);
    sos->addWidget(lso);
    sos->addWidget(qb);
    vig->addWidget(r2);
    vig->addWidget(lvi);
    vig->addWidget(l1);
    vig->setSpacing(50);
    ver->addWidget(r3);
    ver->addWidget(lve);
    ver->addWidget(l2);
    ver->setSpacing(53);
    vb->addLayout(sos);
    vb->addLayout(vig);
    vb->addLayout(ver);
    gb->setLayout(vb);
    ql->addWidget(gb);
    //CheckBox "stringa di cifratura"
    QCheckBox* cb = new QCheckBox("* Mostra stringa di cifratura");
    ql->addWidget(cb);
    ql->setAlignment(cb,Qt::AlignRight);

    //Layout "Testo risultante"
    QLabel* la =new QLabel(tr("Testo risultante:"));
    QTextEdit* t = new QTextEdit();
    t->setReadOnly(true);
    //Layout Pulsanti
    QPushButton* cifra = new QPushButton("Cifra",this);
    QPushButton* decifra = new QPushButton("Decifra",this);
    QPushButton* reset = new QPushButton("Reset",this);
    QPushButton* exit = new QPushButton("Esci",this);
    ql->addWidget(la);
    ql->addWidget(t);
    QHBoxLayout* hb2 = new QHBoxLayout();
    hb2->addWidget(cifra);
    hb2->addWidget(decifra);
    hb2->addWidget(reset);
    hb2->addWidget(exit);
    hb2->setSpacing(10);
    ql->addItem(hb2);
    setLayout(ql);

    //aggiungo i widget creati alla QList<QWidget*>
    Qw << txt << r1 << r2 << r3 << lso << lvi << lve << qb << l1 << l2 << t << cb;

    /* Connect dei pulsanti "Cifra","Decifra","Reset" e "Esci"
       Connect dei QRadioButton per disabilitare quelli non scelti*/
    connect(r1,SIGNAL(clicked()),this,SLOT(disableButton23()));
    connect(r2,SIGNAL(clicked()),this,SLOT(disableButton13()));
    connect(r3,SIGNAL(clicked()),this,SLOT(disableButton12()));
    connect(cifra,SIGNAL(clicked()),this,SLOT(on_cifra_clicked()));
    connect(decifra,SIGNAL(clicked()),this,SLOT(on_decifra_clicked()));
    connect(reset,SIGNAL(clicked()),this,SLOT(on_reset_clicked()));
    connect(exit,SIGNAL(clicked()),qApp,SLOT(quit()));
}
Widget::~Widget(){
    delete ui;
}
void Widget::on_cifra_clicked(){
    QRadioButton* rb1 = dynamic_cast<QRadioButton*>(Qw.at(1));
    QRadioButton* rb2 = dynamic_cast<QRadioButton*>(Qw.at(2));
    QRadioButton* rb3 = dynamic_cast<QRadioButton*>(Qw.at(3));
    QCheckBox* cb1 = dynamic_cast<QCheckBox*>(Qw.at(11));
    QString q = dynamic_cast<QTextEdit*>(Qw.at(0))->toPlainText(); //prelevo frase inserita
    QMessageBox msg;
    msg.setWindowTitle("ERRORE");
    /* Se la frase non è stata inserita o/e non è stato scelto nessun cifrario mando in output un messagio di
       errore */
    if(q == "" && !rb1->isChecked() && !rb2->isChecked() && !rb3->isChecked()){
        msg.setText("Non hai inserito la frase e scelto il cifrario!");
        msg.exec();
    }
    else{
        if(q == ""){
            msg.setText("Non hai inserito la frase");
            msg.exec();
        }
        else{
            if(!rb1->isChecked() && !rb2->isChecked() && !rb3->isChecked()){
                msg.setText("Non hai selezionato alcun cifrario!");
                msg.exec();
            }
            /* Se è stata inserita una frase e scelto un cifrario inizia la cifratura operando con il cifrario
               scelto */
            else{
                if(rb1->isChecked()){
                    withSostituzione();
                    if(cb1->isChecked()){
                        msg.setText("Stringa di cifratura non disponibile per questo tipo di cifrario!");
                        msg.exec();
                        dynamic_cast<QCheckBox*>(Qw.at(11))->setChecked(false);
                    }
                }
                if(rb2->isChecked()) withVigenere();
                if(rb3->isChecked()) withVernam();
            }
        }
    }
}
void Widget::on_decifra_clicked(){
    QRadioButton* rb1 = dynamic_cast<QRadioButton*>(Qw.at(1));
    QRadioButton* rb2 = dynamic_cast<QRadioButton*>(Qw.at(2));
    QRadioButton* rb3 = dynamic_cast<QRadioButton*>(Qw.at(3));
    QString q = dynamic_cast<QTextEdit*>(Qw.at(0))->toPlainText(); //prelevo frase inserita
    QMessageBox msg;
    msg.setWindowTitle("ERRORE");
    /* Se la frase non è stata inserita o/e non è stato scelto nessun cifrario mando in output un messagio di
       errore */
    if(q == "" && !rb1->isChecked() && !rb2->isChecked() && !rb3->isChecked()){ //se vuota e nessun bottone cliccato->errore
        msg.setText("Non hai inserito la frase e scelto il cifrario!");
        msg.exec();
    }
    else{
        if(q == ""){ //se frase vuota->errore
            msg.setText("Non hai inserito la frase");
            msg.exec();
        }
        else{
            if(!rb1->isChecked() && !rb2->isChecked() && !rb3->isChecked()){ // se nessun bottone cliccato->errore
                msg.setText("Non hai selezionato alcun cifrario!");
                msg.exec();
            }
            /* Se è stata inserita una frase e scelto un cifrario inizia la cifratura operando con il cifrario
               scelto. Se è stato scelto il cifrario a sostituzione viene mostrato un messaggio di errore */
            else{ //in base al cifrario scelto viene decifrata la frase
                if(rb1->isChecked()){
                    msg.setText("Operazione non disponibile per la sostituzione!");
                    msg.exec();
                }
                if(rb2->isChecked()) withVigenereRev();
                if(rb3->isChecked()) withVernamRev();
            }
        }
    }
}
/* La frase in chiare viene cifrata con il cifrario a sostituzione */
void Widget::withSostituzione(){
    QString q = dynamic_cast<QTextEdit*>(Qw.at(0))->toPlainText(); //prelevo la frase inserita
    string q1 = q.toLocal8Bit().constData(); //QString -> string
    int n = dynamic_cast<QComboBox*>(Qw.at(7))->currentIndex(); //prelevo il numero di sostituzioni scelto
    F = new Sostituzione(n-1,q1);
    /* Gli indici di QComboBox li associo agli elementi dell'array QStringList cioè il range consentito di spostamenti:
     * 0 -> '-',1 -> '0', 2 -> '1'...
     * Quindi se faccio 1(-1) ottengo lo 0 dell'array e quindi so che il numero di spostamenti sarà 0;
     * se faccio 2(-1) ottengo l'1 dell'array e quindi so che il numero di spostamenti sarà 1 e così via;
     * se faccio 0(-1) ottengo -1 che corrisponde all'elemento '-' dell'array che indica che il numero inserito non
       va bene */
    if(n>0){ //se è stato scelto un numero tra 0-26 compresi avviene la codifica
        F->codifica();
        QString qstr = QString::fromLocal8Bit(F->getRisultato(),F->getPhrase().size()); //char* -> QString
        dynamic_cast<QTextEdit*>(Qw.at(10))->setText(qstr); //stampa della frase cifrata
    }
    delete F;
}
/* La frase in chiare viene cifrata con il cifrario di Vigenère */
void Widget::withVigenere(){
    dynamic_cast<QTextEdit*>(Qw.at(10))->setText("");
    QString q = dynamic_cast<QTextEdit*>(Qw.at(0))->toPlainText(); //prelevo la frase inserita
    string q1 = q.toLocal8Bit().constData(); //QString -> string
    QString q2 = (dynamic_cast<QLineEdit*>(Qw.at(8)))->text(); //prelevo la chiave per la chiave inserita
    string f = q2.toLocal8Bit().constData(); //QString -> string
    F = new Vigenere(f,q1);
    Vigenere* Vi = dynamic_cast<Vigenere*>(F);
    if(f!="" && Vi->getKey()!=""){
        F->codifica();
        QString qstr = QString::fromLocal8Bit(F->getRisultato(),F->getPhrase().size()); //char* -> QString
        dynamic_cast<QTextEdit*>(Qw.at(10))->setText(qstr); //stampa della frase cifrata
        QCheckBox* cb1 = dynamic_cast<QCheckBox*>(Qw.at(11));
        if(cb1->isChecked()){
            dynamic_cast<QTextEdit*>(Qw.at(10))->append("\nStringa di cifratura:");
            qstr = QString::fromLocal8Bit(Vi->getCipherString(),F->getPhrase().size());
            dynamic_cast<QTextEdit*>(Qw.at(10))->append(qstr);
        }
    }
    delete F;
}
/* La frase in chiare viene cifrata con il cifrario di Vernam */
void Widget::withVernam(){
    dynamic_cast<QTextEdit*>(Qw.at(10))->setText("");
    QString q = dynamic_cast<QTextEdit*>(Qw.at(0))->toPlainText(); //prelevo la frase inserita
    string q1 = q.toLocal8Bit().constData(); //QString -> string
    QString q2 = dynamic_cast<QLineEdit*>(Qw.at(9))->text(); //prelevo la chiave per la chiave inserita
    string f = q2.toLocal8Bit().constData(); //QString -> string
    F = new Vernam(f,q1);
    Vernam* Ve = dynamic_cast<Vernam*>(F);
    if(f!="" && Ve->getKey()!=""){
        F->codifica();
        QString qstr = QString::fromLocal8Bit(F->getRisultato(),F->getPhrase().size()); //char* -> QString
        dynamic_cast<QTextEdit*>(Qw.at(10))->setText(qstr); //stampa della frase cifrata
        QCheckBox* cb1 = dynamic_cast<QCheckBox*>(Qw.at(11));
        if(cb1->isChecked()){
            dynamic_cast<QTextEdit*>(Qw.at(10))->append("\nStringa di cifratura:");
            qstr = QString::fromLocal8Bit(Ve->getCipherString(),F->getPhrase().size());
            dynamic_cast<QTextEdit*>(Qw.at(10))->append(qstr);
        }
    }
    delete F;
}
/* La frase in chiare viene decifrata con il cifrario di Vigenère */
void Widget::withVigenereRev(){
    dynamic_cast<QTextEdit*>(Qw.at(10))->setText("");
    QString q = dynamic_cast<QTextEdit*>(Qw.at(0))->toPlainText(); //prelevo la frase inserita
    string q1 = q.toLocal8Bit().constData(); //QString -> string
    QString q2 = (dynamic_cast<QLineEdit*>(Qw.at(8)))->text(); //prelevo la chiave per la chiave inserita
    string f = q2.toLocal8Bit().constData(); //QString -> string
    F = new Vigenere(f,q1);
    Vigenere* Vi = dynamic_cast<Vigenere*>(F);
    if(f!="" && Vi->getKey()!=""){
        Vi->codificaRev();
        QString qstr = QString::fromLocal8Bit(F->getRisultato(),F->getPhrase().size()); //char* -> QString
        dynamic_cast<QTextEdit*>(Qw.at(10))->setText(qstr); //stampa della frase cifrata
        QCheckBox* cb1 = dynamic_cast<QCheckBox*>(Qw.at(11));
        if(cb1->isChecked()){
            dynamic_cast<QTextEdit*>(Qw.at(10))->append("\nStringa di cifratura:");
            qstr = QString::fromLocal8Bit(Vi->getCipherString(),F->getPhrase().size());
            dynamic_cast<QTextEdit*>(Qw.at(10))->append(qstr);
        }
    }
    delete F;
}
/* La frase in chiare viene cifrata con il cifrario di Vernam */
void Widget::withVernamRev(){
    dynamic_cast<QTextEdit*>(Qw.at(10))->setText("");
    QString q = dynamic_cast<QTextEdit*>(Qw.at(0))->toPlainText(); //prelevo la frase inserita
    string q1 = q.toLocal8Bit().constData(); //QString -> string
    QString q2 = dynamic_cast<QLineEdit*>(Qw.at(9))->text(); //prelevo la chiave per la chiave inserita
    string f = q2.toLocal8Bit().constData(); //QString -> string
    F = new Vernam(f,q1);
    Vernam* Ve = dynamic_cast<Vernam*>(F);
    if(f!="" && Ve->getKey()!=""){
        Ve->codificaRev();
        QString qstr = QString::fromLocal8Bit(F->getRisultato(),F->getPhrase().size()); //char* -> QString
        dynamic_cast<QTextEdit*>(Qw.at(10))->setText(qstr); //stampa della frase cifrata
        QCheckBox* cb1 = dynamic_cast<QCheckBox*>(Qw.at(11));
        if(cb1->isChecked()){
            dynamic_cast<QTextEdit*>(Qw.at(10))->append("\nStringa di cifratura:");
            qstr = QString::fromLocal8Bit(Ve->getCipherString(),F->getPhrase().size());
            dynamic_cast<QTextEdit*>(Qw.at(10))->append(qstr);
        }
    }
    delete F;
}
void Widget::on_reset_clicked(){
    //Ogni widget viene riportato al suo stato iniziale
    dynamic_cast<QTextEdit*>(Qw.at(0))->setText("");
    dynamic_cast<QComboBox*>(Qw.at(7))->setCurrentIndex(0);
    dynamic_cast<QLineEdit*>(Qw.at(8))->setText("");
    dynamic_cast<QLineEdit*>(Qw.at(9))->setText("");
    dynamic_cast<QTextEdit*>(Qw.at(10))->setText("");
    dynamic_cast<QCheckBox*>(Qw.at(11))->setChecked(false);
    //Imposto il cifrario Sostituzione come nuovo stato dopo il reset
    dynamic_cast<QRadioButton*>(Qw.at(1))->setChecked(true);
    disableButton23();
}
void Widget::disableButton23(){
    //abilito il pulsante "Sostituzione":Label e ComboBox
    dynamic_cast<QLabel*>(Qw.at(4))->setDisabled(false);
    dynamic_cast<QComboBox*>(Qw.at(7))->setDisabled(false);
    //disabilito i pulsanti "Vigenère" e "Vernam" resettando e disabilitando le loro Label e LineEdit
    dynamic_cast<QLabel*>(Qw.at(5))->setDisabled(true);
    dynamic_cast<QLabel*>(Qw.at(6))->setDisabled(true);
    dynamic_cast<QLineEdit*>(Qw.at(8))->setText("");
    dynamic_cast<QLineEdit*>(Qw.at(8))->setDisabled(true);
    dynamic_cast<QLineEdit*>(Qw.at(9))->setText("");
    dynamic_cast<QLineEdit*>(Qw.at(9))->setDisabled(true);
}
void Widget::disableButton13(){
    //abilito il pulsante "Vigenère":Label e LineEdit
    dynamic_cast<QLabel*>(Qw.at(5))->setDisabled(false);
    dynamic_cast<QLineEdit*>(Qw.at(8))->setDisabled(false);
    //disabilito i pulsanti "Sostituzione" e "Vernam" resettando e disabilitando le loro Label, LineEdit e ComboBox
    dynamic_cast<QLabel*>(Qw.at(4))->setDisabled(true);
    dynamic_cast<QLabel*>(Qw.at(6))->setDisabled(true);
    dynamic_cast<QComboBox*>(Qw.at(7))->setCurrentIndex(0);
    dynamic_cast<QComboBox*>(Qw.at(7))->setDisabled(true);
    dynamic_cast<QLineEdit*>(Qw.at(9))->setText("");
    dynamic_cast<QLineEdit*>(Qw.at(9))->setDisabled(true);
}
void Widget::disableButton12(){
    //abilito il pulsante "Vernam":Label e LineEdit
    dynamic_cast<QLabel*>(Qw.at(6))->setDisabled(false);
    dynamic_cast<QLineEdit*>(Qw.at(9))->setDisabled(false);
    //disabilito i pulsanti "Sostituzione" e "Vigenère" resettando e disabilitando le loro Label, LineEdit e ComboBox
    dynamic_cast<QLabel*>(Qw.at(4))->setDisabled(true);
    dynamic_cast<QComboBox*>(Qw.at(7))->setCurrentIndex(0);
    dynamic_cast<QComboBox*>(Qw.at(7))->setDisabled(true);
    dynamic_cast<QLabel*>(Qw.at(5))->setDisabled(true);
    dynamic_cast<QLineEdit*>(Qw.at(8))->setText("");
    dynamic_cast<QLineEdit*>(Qw.at(8))->setDisabled(true);
}
