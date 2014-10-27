#include "visaoautomato.h"
#include "ui_visaoautomato.h"

VisaoAutomato::VisaoAutomato(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VisaoAutomato)
{
    ui->setupUi(this);

    QString defaultText("");
    bool ok;
    QString caseInput = QInputDialog::getText(this, tr("Titulo"), tr("Digite o nome dos estados, separados por vírgulas:"), QLineEdit::Normal, defaultText, &ok);

    string estados, alfabeto;

    if (ok && !caseInput.isEmpty())
    {
        estados = caseInput.toStdString();
    }

    defaultText = "";
    caseInput = QInputDialog::getText(this, tr("Titulo"), tr("Digite os símbolos do alfabeto, separados por vírgulas::"), QLineEdit::Normal, defaultText, &ok);

    if (ok && !caseInput.isEmpty())
    {
        alfabeto = caseInput.toStdString();
    }

    QStringList nomesEstados;
    vector<string> nomes = separarParametros(estados, ",");
    cout << "numero de estados: " << nomes.size() << endl;
    for (int i = 0; i < nomes.size(); ++i) {
        string aux = nomes.at(i);
        nomesEstados << aux.c_str();
    }

    QStringList simbolosAlfabeto;
    vector<string> simbolos = separarParametros(alfabeto, ",");
    cout << "numero de simbolos: " << simbolos.size() << endl;
    for (int i = 0; i < simbolos.size(); ++i) {
        string aux = simbolos.at(i);
        simbolosAlfabeto << aux.c_str();
    }

    QStandardItemModel * model = new QStandardItemModel(simbolos.size(), nomes.size(), this);

    model->setHorizontalHeaderLabels(nomesEstados);
    model->setVerticalHeaderLabels(simbolosAlfabeto);

    ui->tableView->setModel(model);
}

vector<string> VisaoAutomato::separarParametros(string comando, string delimiter) {
    vector<string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = comando.find(delimiter)) != std::string::npos) {
        token = comando.substr(0, pos);
        tokens.push_back(token);
        comando.erase(0, pos + delimiter.length());
    }
    tokens.push_back(comando);
    return tokens;
}

VisaoAutomato::~VisaoAutomato()
{
    delete ui;
}
