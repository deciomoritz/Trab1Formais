#include "estado.h"
Estado::Estado()
{
    _nome = ' ';
}

Estado::Estado(Simbolo nome){
    _nome = nome;
}
Estado::Estado(string nome, unordered_map<Simbolo, set<Estado*> > delta){
    _nome = nome;
    _delta = delta;
}

string Estado::nome() const{
    return _nome;
}

Estado Estado::copiarEstado() const{
    return Estado(this->_nome, this->_delta);
}

set<Estado*> Estado::getTransicao(Simbolo s) const{
	return _delta.at(s);
}

set<Estado*> Estado::fecho(set<Estado*> visitados){

    visitados.insert(this);

    set<Estado*> adjacentes = _delta['&'];
    for(auto iterAdj = adjacentes.begin(); iterAdj != adjacentes.end();iterAdj++){
        Estado * adj = *iterAdj;

        if(visitados.find(adj) == visitados.end()){//se n contém
            return adj->fecho(visitados);
        }
    }
    return visitados;
}

set<Estado*> Estado::fecho(){
    set<Estado*> visitados;
    return fecho(visitados);
}

void Estado::insereTransicao(Simbolo s, Estado * q){
//    set<Estado*> novo = {q};
//    if(_delta.find(s) != _delta.end()){
//        set<Estado*> atual =_delta.at(s);
//        novo.insert(atual.begin(), atual.end());
//    }
//    _delta[s] = novo;
    set<Estado*> & novo = _delta[s];
    novo.insert(q);
}

Estado::Estado(set<Estado*> estados){
    string nome;
    for(auto iter = estados.begin(); iter != estados.end();iter++){
        Estado * e = *iter;
        nome += e->nome();
    }
    _nome = nome;
}
