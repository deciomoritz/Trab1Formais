#ifndef VISAOAUTOMATO_H
#define VISAOAUTOMATO_H

#include <QMainWindow>

#include <qinputdialog.h>

#include "ui_visaoautomato.h"

#include <QStandardItemModel>

#include <QTableWidgetItem>

#include <QMessageBox>

#include "iostream"
#include <vector>
#include <string>

#include "automato.h"
#include "expressaoregular.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

namespace Ui {
class VisaoAutomato;
}

class VisaoAutomato : public QMainWindow
{
    Q_OBJECT
    int numeroDeEstados, tamanhoDoAlfabeto;

public:
    explicit VisaoAutomato(QWidget *parent = 0);
    ~VisaoAutomato();

public slots:
    void ERParaAF();
    void determinizar();
    void minimizar();

    void diferenca();
    void interseccao();
    void equivalencia();

    void enumerar();
    void encontrarOcorrencias();

private:
    Ui::VisaoAutomato *ui;
    Automato afnd;
    Automato afd;
    Automato minimo;

    vector<string> separarParametros(string comando, string delimiter);

    set<int> procura_string(string padrao, string texto);


};

#endif // VISAOAUTOMATO_H
