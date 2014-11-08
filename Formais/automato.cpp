#include "automato.h"

Automato::Automato(){}
void Automato::deletar(){
       for(auto A = _estados.begin(); A != _estados.end();A++){
           delete *A;
       }
       cout<< "DELETADO" << endl;
};
Automato::Automato(set<string> alf, Estado *inicial){
    alfabeto = alf;
    q0 = inicial;
    _estados.insert(inicial);
}
Automato::Automato(set<Estado*> estados, set<Simbolo> alf, Estado *inicial, set<Estado*> finais){
    alfabeto = alf;
    q0 = inicial;
    _estados = estados;
    _finais = finais;
}

representacaoDoEstado Automato::fecho_K(){
	representacaoDoEstado fecho_Ki;
	for(auto A = _estados.begin(); A != _estados.end();A++){

            fecho_Ki.map.insert({(*A)->nome(), (*A)->fecho()});
		}
	return fecho_Ki;
}
/*Estado Automato::getEstado(int i)
{
    set<Estado>::iterator it;
    for(it=estados.begin();it=estados.end();it++ )
    return *it;
}*/

void Automato::add(Estado *e){
    for(auto iterador = _estados.begin(); iterador != _estados.end();iterador++){
        Estado * existente = *iterador;

        if(existente->nome().compare(e->nome()) == 0)
            return;
    }
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
	representacaoDoEstado fecho = fecho_K();
	representacaoDoEstado estados_determinizados;
	char nome_c	= 'A';
    string nome;
    unordered_map<string, Estado*> simbolo_estado;
    set<Estado*> novo_em_det, novo_det_temp;
    nome = string(1,nome_c++);
    Estado *novo = new Estado(nome);
    estados_determinizados.map.insert({novo->nome(), fecho.map.at(q0->nome())});
    novo_em_det.insert(novo);
    nome = novo->nome();
    simbolo_estado.insert({nome, novo});
	while(!novo_em_det.empty()){ //enquanto forem adicionados novos estados ao automato determinizado
		novo_det_temp.clear();
		for(auto A = novo_em_det.begin(); A != novo_em_det.end();A++){ // pra cada novo estado
            nome = (*A)->nome();
            set<Estado*> representacao = estados_determinizados.map.at(nome);

			for(auto a = alfabeto.begin(); a != alfabeto.end();a++){ //para cada símbolo do alfabeto
                bool flag_novo = true;
                set<Estado*> transicao_A;
                set<Estado*> transicao_novo;
				for(auto B = representacao.begin(); B != representacao.end();B++){//para cada estado do conjunto de estados que A representa
                    set<Estado*> transicao_B = (*B)->getTransicao(*a);
                    transicao_A.insert(transicao_B.begin(), transicao_B.end()); //nova transição para um conjunto de estados a partir de cada um dos estados que A representa
				}
				for(auto C = transicao_A.begin(); C != transicao_A.end();C++){//para cada estado que pode ser alcançado pelos estados que A representa
                    nome = (*C)->nome();
                    transicao_novo.insert(fecho.map[nome].begin(), fecho.map[nome].end()); //nova transição para um conjunto de estados a partir de cada um dos estados
				}
				for(auto D = estados_determinizados.map.begin(); D != estados_determinizados.map.end();D++){ //para cada estado já existente no automato, verificar se o novo já existe.
					if(D->second==transicao_novo){//o estado destino já existe.
						flag_novo = false;

                        (*A)->insereTransicao(*a, simbolo_estado.at(D->first));
					}
				}
				if(flag_novo){
                    nome = string(1,nome_c++);
                    Estado *novo2 = new Estado(nome);
                    nome = novo2->nome();
                    simbolo_estado.insert({nome, novo2});
                    estados_determinizados.map.insert({nome,transicao_novo});
                    (*A)->insereTransicao(*a, novo2);
                    novo_det_temp.insert(novo2);
				}
			}
		}
		novo_em_det = novo_det_temp;
	}
	Automato deterministico;
    deterministico.q0 = novo;
	deterministico.alfabeto = alfabeto;
    set<Estado*> finais, estados;
	for(auto A = estados_determinizados.map.begin(); A != estados_determinizados.map.end();A++){ //para cada estado do automato

        estados.insert(simbolo_estado[(A->first)]);
		for(auto B = A->second.begin(); B != A->second.end();B++){//para cada estado que A representa
			for(auto F = _finais.begin(); F != _finais.end();F++){//para cada estado final do atual
                Estado* x = *B;
                Estado *y = *F;
                if(x->nome().compare(y->nome())==0){
                    finais.insert(simbolo_estado[(A->first)]);
				}
			}
		}
	}
	deterministico._estados = estados;
	deterministico._finais = finais;
	return deterministico;
}

    set<Estado*> Automato::getEstados(){return _estados;}

    set<Estado*> Automato::getFinais(){return _finais;}

    set<Simbolo> Automato::getAlfabeto(){return alfabeto;}

    Estado* Automato::getInicial(){return q0;}


/*
Automato Automato::getMinimo();*/
