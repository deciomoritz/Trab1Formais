#ifndef VISAOAUTOMATO_H
#define VISAOAUTOMATO_H

#include <QMainWindow>

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
};

#endif // VISAOAUTOMATO_H
