#include "visaoautomato.h"
#include "ui_visaoautomato.h"

#include <qinputdialog.h>

#include "iostream"

using std::cout;
using std::endl;

VisaoAutomato::VisaoAutomato(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VisaoAutomato)
{
    ui->setupUi(this);

    QString defaultText("");
    bool ok;
    QString caseInput = QInputDialog::getText(this, tr("Titulo"), tr("Digite o número de estados:"), QLineEdit::Normal, defaultText, &ok);

    if (ok && !caseInput.isEmpty())
    {
        numeroDeEstados = caseInput.toInt();
    }

    defaultText = "";
    caseInput = QInputDialog::getText(this, tr("Titulo"), tr("Digite o tamanho do alfabeto:"), QLineEdit::Normal, defaultText, &ok);

    if (ok && !caseInput.isEmpty())
    {
        tamanhoDoAlfabeto = caseInput.toInt();
    }

    cout << numeroDeEstados << "  " << tamanhoDoAlfabeto << endl;


}

VisaoAutomato::~VisaoAutomato()
{
    delete ui;
}
