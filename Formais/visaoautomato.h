#ifndef VISAOAUTOMATO_H
#define VISAOAUTOMATO_H

#include <QMainWindow>

#include <qinputdialog.h>

#include <QStandardItemModel>

#include "iostream"
#include <vector>
#include <string>

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

private:
    Ui::VisaoAutomato *ui;

    vector<string> separarParametros(string comando, string delimiter);
};

#endif // VISAOAUTOMATO_H
