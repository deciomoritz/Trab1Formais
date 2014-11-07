#include "automato.h"

Automato::Automato(){}

Automato::Automato(set<Simbolo> alf, Estado inicial){
    alfabeto = alf;
    q0 = inicial;
    _estados.insert(inicial);
}

representacaoDoEstado Automato::fecho_K(){
	representacaoDoEstado fecho;
	set<Estado*> temp;
	for(auto A = _estados.begin(); A != _estados.end();A++){
		temp = (*A).fecho();
		//fecho.map.insert(A, );
	}
	return fecho;
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

}

/*
Automato Automato::getMinimo();*/
