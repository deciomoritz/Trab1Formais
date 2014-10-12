#ifndef AUTOMATO_H
#define AUTOMATO_H

#include <vector>
using std::vector;

#include "estado.h"

class Automato
{
    vector<Estado> _estados;

public:

    Automato();

    Estado getEstado(int i);
    void add(Estado e);
    void remove(string nome);
};

#endif
