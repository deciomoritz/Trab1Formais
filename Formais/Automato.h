#ifndef AUTOMATO_H
#define AUTOMATO_H

#include <set>
using std::set;

#include "Estado.h"
struct representacaoDoEstado{
    unordered_map<Simbolo, set<Estado>> map;
};

class Automato
{
    set<Estado> _estados, _finais;
    Estado q0;
    set<Simbolo> alfabeto;

public:

    Automato();
    Automato(set<Simbolo> alf, Estado inicial);
    Automato determinizar();

/*
    Estado getEstado(int i);*/
    void add(Estado e);
    /*void remove(string nome);*/

    };

#endif
