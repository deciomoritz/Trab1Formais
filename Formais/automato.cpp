#include "automato.h"

Automato::Automato(){}

Automato::Automato(set<Simbolo> alf, Estado inicial){
    alfabeto = alf;
    q0 = inicial;
    _estados.insert(inicial);
}

/*Estado Automato::getEstado(int i)
{
    set<Estado>::iterator it;
    for(it=estados.begin();it=estados.end();it++ )
    return *it;
}*/

void Automato::add(Estado e){
    _estados.insert(e);
}
/*
void Automato::remove(string nome){
    for (unsigned i = 0; i < _estados.size(); ++i) {
        Estado e = _estados.at(i);
        if(e.nome() == nome)
            _estados.erase(_estados.begin() + i);
    }
}*/

Automato Automato::determinizar(){

    set<Estado*> novoAFD;
    novoAFD.insert(&q0);
    unordered_map<Simbolo, set<Estado*> > novoDelta;

    for(auto novoAF = novoAFD.begin(); novoAF != novoAFD.end();novoAF++){
        Estado * atual = *novoAF;

        for(auto iterAlfabeto = alfabeto.begin(); iterAlfabeto != alfabeto.end();iterAlfabeto++){
            Simbolo simbolo = *iterAlfabeto;
            set<Estado*> fecho = atual->fecho(); //e-fecho

            fecho.insert(novoDelta[simbolo].cbegin(), novoDelta[simbolo].cend());//e-fecho U novoDelta[simbolo]

            Estado novoEstado(fecho);
            if(novoAFD.find(&novoEstado) != novoAFD.end()){//se não existe
                novoAFD.insert(&novoEstado);

                set<Estado*> aux; //só pra dizer que o novoEstado é um conjunto
                aux.insert(&novoEstado);
                pair<Simbolo, set<Estado*> > elemento(simbolo, aux);

                novoDelta.insert(elemento);//cria transição simbolo, novoEstado
            }
        }
    }
}

/*
Automato Automato::getMinimo();*/
