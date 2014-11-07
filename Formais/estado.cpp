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

set<Estado*> Estado::getTransicao(Simbolo s) const{
	return _delta.at(s);
}
set<Estado*> Estado::fecho(){
	set<Estado*> N0,N1, temp;
	N0.insert(this);
	bool different = true;
	while(different){
		N1 = N0;
		for(auto A = N0.begin(); A != N0.end();A++){
			temp = (*(*A))._delta['&'];
			N1.insert(temp.begin(),temp.end());
		}
		if(N1==N0){
			different = false;
		}
		N0 = N1;
	};
	return N1;
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
