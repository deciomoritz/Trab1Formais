#include "visaoautomato.h"

set<int> VisaoAutomato::procura_string(string padrao, string texto){
    set<int> posicoes;
    ExpressaoRegular er;
    Automato maq_temp = er.ERParaAFND(padrao);
    Automato maq = maq_temp.determinizar();
    Estado *atual;
    set<Estado*> temp,finais;
    finais = maq.getFinais();
    Estado *proximo;
    set<string> alfabeto = maq.getAlfabeto();
    for(int i = 0;i<texto.length();i++){\
        proximo = maq.getInicial();
        for(int j =i; j<texto.length();j++){
            atual = proximo;
            string entrada = string(1,texto[j]);
            if(alfabeto.find(entrada)==alfabeto.end()){
                atual = maq.getInicial();
                break;
            }
            temp = atual->getTransicao(entrada);
            proximo = *(temp.begin());
            if(finais.find(proximo)!=finais.end()){
                i=j-padrao.length()+1;
                posicoes.insert(i);
                j = texto.length();
            }
        }
    }
    if(posicoes.empty()){
        posicoes.insert(-1);
    }
    maq.deletar();
    maq_temp.deletar();
    return posicoes;
}

VisaoAutomato::VisaoAutomato(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VisaoAutomato)
{
    ui->setupUi(this);

    ui->ertext->setText("(ab)");
    connect(ui->OK, SIGNAL(clicked()), this, SLOT(ERParaAF()));

    connect(ui->determinizar, SIGNAL(clicked()), this, SLOT(determinizar()));

    connect(ui->minimizar, SIGNAL(clicked()), this, SLOT(minimizar()));

    connect(ui->diferenca, SIGNAL(clicked()), this, SLOT(diferenca()));

    connect(ui->interseccao, SIGNAL(clicked()), this, SLOT(interseccao()));

    connect(ui->equivalencia, SIGNAL(clicked()), this, SLOT(equivalencia()));

    connect(ui->enumerar, SIGNAL(clicked()), this, SLOT(enumerar()));

    connect(ui->enumerar_2, SIGNAL(clicked()), this, SLOT(encontrarOcorrencias()));
}

void VisaoAutomato::enumerar(){
    int n = ui->n->toPlainText().toInt();

    ExpressaoRegular expReg;

    QString str = ui->ertext2->toPlainText();
    string er = str.toStdString();

    Automato afd = expReg.ERParaAFND(er).determinizar();

    set<string> sentencas = afd.listar_sentencas(n);

    QTextEdit * area = ui->enumeracao;
    area->clear();

    for(auto iterador = sentencas.begin(); iterador != sentencas.end();iterador++){
        string sentenca = *iterador;

        area->append(QString(sentenca.c_str()));
    }
}

void VisaoAutomato::encontrarOcorrencias(){

    string s = ui->ocorrencias->toPlainText().toStdString();

    string padrao = ui->ertext2->toPlainText().toStdString();

    set<int> posicoes = procura_string(padrao,s);

    string retorno = "";

    for(auto iterador = posicoes.begin(); iterador != posicoes.end();iterador++){
        int pos = *iterador;

        retorno += to_string(pos);
        retorno += ", ";
    }
    QMessageBox messageBox;

    messageBox.critical(0,"",retorno.c_str());
}

void VisaoAutomato::diferenca(){
    ExpressaoRegular expReg;

    QString str1 = ui->erA->toPlainText();
    string er1 = str1.toStdString();

    Automato afnd1 = expReg.ERParaAFND(er1);

    QString str2 = ui->erB->toPlainText();
    string er2 = str2.toStdString();

    Automato afnd2 = expReg.ERParaAFND(er2);

    Automato af;
    af = af.diferenca(afnd1, afnd2).minimizar();

    QTableView * tabela = ui->resultado;

    QStringList nomesEstados;

    set<Estado*> estados = af.getEstados();
    set<Estado*> finais = af.getFinais();
    for(auto iterador = estados.begin(); iterador != estados.end();iterador++){
        Estado * e = *iterador;

        if(af.getInicial()->nome().compare(e->nome()) == 0){
            string nome = "->";
            nome.append(e->nome());
            nomesEstados << nome.c_str();
            continue;
        }

        if(finais.find(e) != finais.end()){
            string nome = "*";
            nome.append(e->nome());
            nomesEstados << nome.c_str();
            continue;
        }

        nomesEstados << e->nome().c_str();
    }

    QStringList simbolosAlfabeto;

    set<Simbolo> alfabeto = af.getAlfabeto();
    simbolosAlfabeto << string("&").c_str();
    for(auto iterador = alfabeto.begin(); iterador != alfabeto.end();iterador++){
        Simbolo s = *iterador;
        simbolosAlfabeto << s.c_str();
    }
    alfabeto.insert(string("&").c_str());

    QStandardItemModel * model = new QStandardItemModel(simbolosAlfabeto.size(), nomesEstados.size(), this);

    model->setHorizontalHeaderLabels(simbolosAlfabeto);
    model->setVerticalHeaderLabels(nomesEstados);

    int i = 0;
    int j = 0;

    QStandardItem * celula;
    for(auto iterador = estados.begin(); iterador != estados.end();iterador++){
        Estado * e = *iterador;
        for(auto iteradorB = alfabeto.begin(); iteradorB != alfabeto.end();iteradorB++){
            Simbolo s = *iteradorB;
            set<Estado*> para = e->getTransicao(s);
            Estado * parA = *para.begin();

            if(parA == NULL){
                j++;
                continue;
            }

            celula = new QStandardItem(QString(parA->nome().c_str()));
            model->setItem(i,j,celula);
            j++;
        }
        j = 0;
        i++;
    }

    tabela->setModel(model);

    tabela->resizeColumnsToContents();
    tabela->resizeRowsToContents();
}

void VisaoAutomato::interseccao(){
    ExpressaoRegular expReg;

    QString str1 = ui->erA->toPlainText();
    string er1 = str1.toStdString();

    Automato afnd1 = expReg.ERParaAFND(er1);

    QString str2 = ui->erB->toPlainText();
    string er2 = str2.toStdString();

    Automato afnd2 = expReg.ERParaAFND(er2);

    Automato af;
    af = af.interseccao(afnd1, afnd2).minimizar();

    QTableView * tabela = ui->resultado;

    QStringList nomesEstados;

    set<Estado*> estados = af.getEstados();
    set<Estado*> finais = af.getFinais();
    for(auto iterador = estados.begin(); iterador != estados.end();iterador++){
        Estado * e = *iterador;

        if(af.getInicial()->nome().compare(e->nome()) == 0){
            string nome = "->";
            nome.append(e->nome());
            nomesEstados << nome.c_str();
            continue;
        }

        if(finais.find(e) != finais.end()){
            string nome = "*";
            nome.append(e->nome());
            nomesEstados << nome.c_str();
            continue;
        }

        nomesEstados << e->nome().c_str();
    }

    QStringList simbolosAlfabeto;

    set<Simbolo> alfabeto = af.getAlfabeto();
    simbolosAlfabeto << string("&").c_str();
    for(auto iterador = alfabeto.begin(); iterador != alfabeto.end();iterador++){
        Simbolo s = *iterador;
        simbolosAlfabeto << s.c_str();
    }
    alfabeto.insert(string("&").c_str());

    QStandardItemModel * model = new QStandardItemModel(simbolosAlfabeto.size(), nomesEstados.size(), this);

    model->setHorizontalHeaderLabels(simbolosAlfabeto);
    model->setVerticalHeaderLabels(nomesEstados);

    int i = 0;
    int j = 0;

    QStandardItem * celula;
    for(auto iterador = estados.begin(); iterador != estados.end();iterador++){
        Estado * e = *iterador;
        for(auto iteradorB = alfabeto.begin(); iteradorB != alfabeto.end();iteradorB++){
            Simbolo s = *iteradorB;
            set<Estado*> para = e->getTransicao(s);
            Estado * parA = *para.begin();

            if(parA == NULL){
                j++;
                continue;
            }

            celula = new QStandardItem(QString(parA->nome().c_str()));
            model->setItem(i,j,celula);
            j++;
        }
        j = 0;
        i++;
    }

    tabela->setModel(model);

    tabela->resizeColumnsToContents();
    tabela->resizeRowsToContents();
}

void VisaoAutomato::equivalencia(){
    ExpressaoRegular expReg;

    QString str1 = ui->erA->toPlainText();
    string er1 = str1.toStdString();

    Automato afnd1 = expReg.ERParaAFND(er1);

    QString str2 = ui->erB->toPlainText();
    string er2 = str2.toStdString();

    Automato afnd2 = expReg.ERParaAFND(er2);

    bool equivalentes = afnd1.determinizar().equivalencia(afnd2.determinizar());

    QMessageBox messageBox;

    if(equivalentes)
        messageBox.critical(0,"","Equivalentes!");
    else
        messageBox.critical(0,"","Não equivalentes!");
}

void VisaoAutomato::minimizar(){
    Automato minimo = this->afnd.minimizar();
    this->minimo = minimo;

    QTableView * tabela = ui->minimo;

    QStringList nomesEstados;

    set<Estado*> estados = minimo.getEstados();
    set<Estado*> finais = minimo.getFinais();
    for(auto iterador = estados.begin(); iterador != estados.end();iterador++){
        Estado * e = *iterador;

        if(minimo.getInicial()->nome().compare(e->nome()) == 0){
            string nome = "->";
            nome.append(e->nome());
            nomesEstados << nome.c_str();
            continue;
        }

        if(finais.find(e) != finais.end()){
            string nome = "*";
            nome.append(e->nome());
            nomesEstados << nome.c_str();
            continue;
        }

        nomesEstados << e->nome().c_str();
    }

    QStringList simbolosAlfabeto;

    set<Simbolo> alfabeto = minimo.getAlfabeto();
    for(auto iterador = alfabeto.begin(); iterador != alfabeto.end();iterador++){
        Simbolo s = *iterador;
        simbolosAlfabeto << s.c_str();
    }

    QStandardItemModel * model = new QStandardItemModel(simbolosAlfabeto.size(), nomesEstados.size(), this);

    model->setHorizontalHeaderLabels(simbolosAlfabeto);
    model->setVerticalHeaderLabels(nomesEstados);

    int i = 0;
    int j = 0;

    QStandardItem * celula;
    for(auto iterador = estados.begin(); iterador != estados.end();iterador++){
        Estado * e = *iterador;
        for(auto iteradorB = alfabeto.begin(); iteradorB != alfabeto.end();iteradorB++){
            Simbolo s = *iteradorB;
            set<Estado*> para = e->getTransicao(s);
            Estado * parA = *para.begin();

            if(parA == NULL){
                j++;
                continue;
            }

            celula = new QStandardItem(QString(parA->nome().c_str()));
            model->setItem(i,j,celula);
            j++;
        }
        j = 0;
        i++;
    }

    tabela->setModel(model);

    tabela->resizeColumnsToContents();
    tabela->resizeRowsToContents();
}

void VisaoAutomato::determinizar(){

    Automato afd = this->afnd.determinizar();
    this->afnd = afd;

    QTableView * tabela = ui->afd;

    QStringList nomesEstados;

    set<Estado*> estados = afnd.getEstados();
    set<Estado*> finais = afnd.getFinais();
    for(auto iterador = estados.begin(); iterador != estados.end();iterador++){
        Estado * e = *iterador;

        if(afnd.getInicial()->nome().compare(e->nome()) == 0){
            string nome = "->";
            nome.append(e->nome());
            nomesEstados << nome.c_str();
            continue;
        }

        if(finais.find(e) != finais.end()){
            string nome = "*";
            nome.append(e->nome());
            nomesEstados << nome.c_str();
            continue;
        }

        nomesEstados << e->nome().c_str();
    }

    QStringList simbolosAlfabeto;

    set<Simbolo> alfabeto = afnd.getAlfabeto();
    for(auto iterador = alfabeto.begin(); iterador != alfabeto.end();iterador++){
        Simbolo s = *iterador;
        simbolosAlfabeto << s.c_str();
    }

    QStandardItemModel * model = new QStandardItemModel(simbolosAlfabeto.size(), nomesEstados.size(), this);

    model->setHorizontalHeaderLabels(simbolosAlfabeto);
    model->setVerticalHeaderLabels(nomesEstados);

    int i = 0;
    int j = 0;

    QStandardItem * celula;
    for(auto iterador = estados.begin(); iterador != estados.end();iterador++){
        Estado * e = *iterador;
        for(auto iteradorB = alfabeto.begin(); iteradorB != alfabeto.end();iteradorB++){
            Simbolo s = *iteradorB;
            set<Estado*> para = e->getTransicao(s);
            Estado * parA = *para.begin();

            if(parA == NULL){
                j++;
                continue;
            }

            celula = new QStandardItem(QString(parA->nome().c_str()));
            model->setItem(i,j,celula);
            j++;
        }
        j = 0;
        i++;
    }

    tabela->setModel(model);

    tabela->resizeColumnsToContents();
    tabela->resizeRowsToContents();
}

void VisaoAutomato::ERParaAF(){
    QString str = ui->ertext->toPlainText();
    string er = str.toStdString();

    ExpressaoRegular expReg;
    Automato afnd = expReg.ERParaAFND(er);
    this->afnd = afnd;

    QTableView * tabela = ui->er;

    QStringList nomesEstados;

    set<Estado*> estados = afnd.getEstados();
    set<Estado*> finais = afnd.getFinais();
    for(auto iterador = estados.begin(); iterador != estados.end();iterador++){
        Estado * e = *iterador;

        if(afnd.getInicial()->nome().compare(e->nome()) == 0){
            string nome = "->";
            nome.append(e->nome());
            nomesEstados << nome.c_str();
            continue;
        }

        Estado * final = *finais.begin();
        if(e->nome().compare(final->nome()) == 0){
            string nome = "*";
            nome.append(e->nome());
            nomesEstados << nome.c_str();
            continue;
        }

        nomesEstados << e->nome().c_str();
    }

    QStringList simbolosAlfabeto;

    set<Simbolo> alfabeto = afnd.getAlfabeto();
    simbolosAlfabeto << string("&").c_str();
    for(auto iterador = alfabeto.begin(); iterador != alfabeto.end();iterador++){
        Simbolo s = *iterador;
        simbolosAlfabeto << s.c_str();
    }
    alfabeto.insert(string("&").c_str());

    QStandardItemModel * model = new QStandardItemModel(simbolosAlfabeto.size(), nomesEstados.size(), this);

    model->setHorizontalHeaderLabels(simbolosAlfabeto);
    model->setVerticalHeaderLabels(nomesEstados);

    int i = 0;
    int j = 0;

    QStandardItem * celula;
    for(auto iterador = estados.begin(); iterador != estados.end();iterador++){
        Estado * e = *iterador;
        for(auto iteradorB = alfabeto.begin(); iteradorB != alfabeto.end();iteradorB++){
            Simbolo s = *iteradorB;
            set<Estado*> para = e->getTransicao(s);
            Estado * parA = *para.begin();

            if(parA == NULL){
                j++;
                continue;
            }

            celula = new QStandardItem(QString(parA->nome().c_str()));
            model->setItem(i,j,celula);
            j++;
        }
        j = 0;
        i++;
    }

    tabela->setModel(model);

    tabela->resizeColumnsToContents();
    tabela->resizeRowsToContents();
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
