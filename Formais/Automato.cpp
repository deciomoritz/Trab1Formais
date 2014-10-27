#include "Automato.h"

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

    unordered_map<Simbolo, set<Estado>> map;
    set<Estado> representacao;
    representacao = q0.fecho(representacao);
    char nome = 'A';
    Estado q0('A');
    map.insert({nome,representacao});
    Automato det(alfabeto, q0);
    set<Estado>::iterator i,k;
    set<Simbolo>::iterator j;
    set<Estado> transita, aux1, aux2;
    for(i = det._estados.begin(); i!= det._estados.end();i++){
    	for(j= alfabeto.begin();j!= alfabeto.end();j++){
    		transita.clear();
    		Estado novo;
    		representacao = map.at((*i).nome());
    		for(k = representacao.begin(); k!=representacao.end(); k++){
    			aux1 = (*k).getTransicao((*j));
    			transita.insert(aux.begin(), aux.end());
    		}
    		aux.clear();
    		for(k =transita.begin(); k!=transita.end(); k++){

    			aux.insert( = set_union(fecho2, transita.at(i).fecho(vazio) )
    		}

    		if(det.contemK(novo)) //avalia se contem a representação, não o nome;
    			det.insereTransição(alfabeto(j), det.getK(fecho2))
    		else{
    			nome++;
    			novo(nome);
    			map.insert({nome,fecho2});
    		}
    	}
    }

   }

}
/*
Automato Automato::getMinimo();*/
