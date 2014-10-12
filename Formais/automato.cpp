#include "automato.h"

Automato::Automato()
{

}

Estado Automato::getEstado(int i)
{
    return _estados.at(i);
}

void Automato::add(Estado e){
    _estados.push_back(e);
}

void Automato::remove(string nome){
    for (unsigned i = 0; i < _estados.size(); ++i) {
        Estado e = _estados.at(i);
        if(e.nome() == nome)
            _estados.erase(_estados.begin() + i);
    }
}
