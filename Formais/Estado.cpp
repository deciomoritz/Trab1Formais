#include "Estado.h"
Estado::Estado()
{
    _nome = ' ';
}

Estado::Estado(Simbolo nome){
    _nome = nome;
}
Estado::Estado(Simbolo nome, unordered_map<Simbolo, set<Estado> > delta){
    _nome = nome;
    _delta = delta;
}

Simbolo Estado::nome() const{
    return _nome;
}

Estado Estado::copiarEstado() const{
    return Estado(this->_nome, this->_delta);
}

set<Estado> Estado::getTransicao(Simbolo s) const{
	return _delta.at(s);
}

set<Estado> Estado::fecho(set<Estado> conj) const{
    set<Estado> retorno, adjacentes, aux, novo;
    retorno = conj;
    adjacentes= _delta.at('&');
    aux.insert(copiarEstado()); //encontrar forma de inserir próprio estado

    set<Estado>::iterator i,j;
    bool stop;
    for(i =adjacentes.begin(); i != adjacentes.end(); i++){
        stop = false;
        for(j=retorno.begin();j!= retorno.end() || stop;j++){//procurar forma melhor de parar iterador
                if((*i)==(*j))
                   stop = true;
        }
        if(!stop){
        	aux =(*i).fecho(retorno);
        	retorno.insert(aux.begin(),aux.end());
        }
    }
    return retorno;
}
