#include <iostream>

#include "estado.h"
#include "automato.h"
#include "expressaoregular.h"

#include "visaoautomato.h"

#include <QApplication>

using std::cout;
using std::endl;

set<int> procura_string(string padrao, string texto){
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

void print_automato(Automato af){
    set<Estado*> K = af.getEstados();
    set<Estado*> finais = af.getFinais();
    set<string> alfabeto = af.getAlfabeto();
    alfabeto.insert("&");
    Estado *inicial = af.getInicial();
	//inicial
	cout << "================= " << endl;
    cout << "INICIAL: " << inicial->nome() << endl;
	//transições
	cout << "TRANSIÇÕES: " << endl;
	for(auto A = K.begin(); A != K.end();A++){
		for(auto a = alfabeto.begin(); a != alfabeto.end();a++){
            string s = *a;
            Estado* e = *A;
            set<Estado*> transicoes = e->getTransicao(s);
			if(!transicoes.empty()){
				for(auto B = transicoes.begin(); B != transicoes.end();B++){
                    cout << (*A)->nome() <<",  "<< *a <<" -> " <<  (*B)->nome() << endl;
				}
			}
		}
	}
	//Finais
	cout << "FINAIS: " << endl;
	for(auto F = finais.begin(); F != finais.end();F++){
        cout << (*F)->nome() << endl;
	}
	cout << "================= " << endl;
}
int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    VisaoAutomato visao;
//    visao.show();
//    return a.exec();

//    Arvore a;
//    a.montarArvore("(aa|bb|(ab)(aa|bb)*(ab|ba))*");

    ExpressaoRegular er;
//    er.ERParaAFND3("(((a.a)|(b.b)|((a.b)|(b.a)).((a.a|(b.b))*).((a.b)|(b.a)))*)");

        Automato af = er.ERParaAFND("(a?)").minimizar();
//        print_automato(af);
        af = er.concatena("abc").minimizar();
        Automato::print(af);

}
