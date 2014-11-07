

#include <iostream>

#include "estado.h"
#include "automato.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    VisaoAutomato w;
//    w.show();

////    return a.exec();
     Estado a('A'),b('B'),c('C'), d('D');
     a.insereTransicao('&', &b);
     b.insereTransicao('&', &c);
     c.insereTransicao('&', &d);
     d.insereTransicao('&', &b);
     set<Estado*> fecho;

     fecho = b.fecho();
     for(auto iter = fecho.begin(); iter != fecho.end();iter++){
        Estado * e = *iter;
        cout << e->nome();
     }
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
}
