#ifndef AUTOMATO_H
#define AUTOMATO_H

#include <set>
using std::set;

using std::pair;

#include "estado.h"
struct representacaoDoEstado{
    unordered_map<string, set<Estado*>> map;
};

class Automato
{
    set<Estado*> _estados, _finais;
    Estado* q0;
    set<Simbolo> alfabeto;

public:

    Automato();
    Automato(set<string> alf, Estado *inicial);
    Automato(set<Estado*> estados, set<Simbolo> alf, Estado *inicial, set<Estado*> finais);
    representacaoDoEstado fecho_K();
    Automato determinizar();

    Automato complementar();

    void deletar();
/*
    Estado getEstado(int i);*/
    void add(Estado *e);
    /*void remove(string nome);*/

    set<Estado*> getEstados();
    set<Estado*> getFinais();
    set<Simbolo> getAlfabeto();
    Estado* getInicial();
    };

#endif
