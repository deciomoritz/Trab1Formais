

#include <iostream>

#include "estado.h"
#include "automato.h"
#include "mainwindow.h"
using std::cout;
using std::endl;

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
//    VisaoAutomato w;
//    w.show();

////    return a.exec();
     Estado a("A"),b("B"),c("C"), d("D");
     a.insereTransicao("&", &b);
     a.insereTransicao("&", &d);
     a.insereTransicao("a", &a);
     a.insereTransicao("b", &a);
     b.insereTransicao("a", &c);
     d.insereTransicao("b", &d);
     d.insereTransicao("b", &b);
     set<Estado*> ashua;
     ashua.insert(&a);
     ashua.insert(&b);
     ashua.insert(&c);
             for(auto iter = ashua.begin(); iter != ashua.end();iter++){
                Estado * e = *iter;
                cout << e->nome() << endl;
             }
    // b<a; a<b;b<c;c<b;
     set<Estado*> fecho;
     set<Estado*> estados;
     estados.insert(&a);
     estados.insert(&b);
     estados.insert(&c);
     estados.insert(&d);
     set<Simbolo> alf;
     alf.insert("a");
     alf.insert("b");
     set<Estado*> finais;
     finais.insert(&d);

     /*fecho = a.fecho();
     for(auto iter = fecho.begin(); iter != fecho.end();iter++){
        Estado * e = *iter;
        cout << e->nome() << endl;
     }*/
     Automato afnd(estados, alf, &a,finais);
     print_automato(afnd);
     Automato mortal = afnd.determinizar();
     print_automato(mortal);
/*
    //exemplo linguagem (a,b)*abb q o olinto passou
     Estado a('A'),b('B'),c('C'), d('D');
     a.insereTransicao('a', &a);
     a.insereTransicao('a', &b);
     a.insereTransicao('b', &a);
     b.insereTransicao('b', &c);
     c.insereTransicao('b', &d);

    set<Simbolo> alfabeto;
    alfabeto.insert('a');
    alfabeto.insert('b');

    Automato af(alfabeto, a);
    af.add(b);
    af.add(c);

//    set<Estado*> fecho = a.fecho();

//    for(auto iter = fecho.begin(); iter != fecho.end();iter++){
//        Estado * e = *iter;
//        cout << e->nome();
//    }

 //   af.determinizar();
*/
     //afnd.deletar();
     mortal.deletar();
     cout << "ao menos acabou" << endl;
}
