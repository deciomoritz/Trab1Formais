#include "automato.h"

Automato::Automato(){}

Automato::Automato(set<Simbolo> alf, Estado inicial){
    alfabeto = alf;
    q0 = inicial;
    _estados.insert(inicial);
}

representacaoDoEstado Automato::fecho_K(){
    representacaoDoEstado fecho_Ki;
    for(auto A = _estados.begin(); A != _estados.end();A++){
            Estado e = (*A);
            fecho_Ki.map.insert({&e, e.fecho()});
        }
    return fecho_Ki;
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
    representacaoDoEstado fecho = fecho_K();
    representacaoDoEstado estados_determinizados;
    char nome_c = 'A';
    set<Estado*> novo_em_det, novo_det_temp;
    Estado novo;
    estados_determinizados.map.insert({&novo, fecho.map[&q0]});
    novo_em_det.insert(&novo);
    while(!novo_em_det.empty()){ //enquanto forem adicionados novos estados ao automato determinizado
        //string nome(stringnome_c++);
        //Estado n(string(nome_c++));
        novo_det_temp.clear();
        for(auto A = novo_em_det.begin(); A != novo_em_det.end();A++){ // pra cada novo estado

            bool flag_novo = true;
            set<Estado*> representacao = estados_determinizados.map.at(*A);
            set<Estado*> transicao_novo;
            for(auto a = alfabeto.begin(); a != alfabeto.end();a++){ //para cada símbolo do alfabeto
                set<Estado*> transicao_A;
                for(auto B = representacao.begin(); B != representacao.end();B++){//para cada estado do conjunto de estados que A representa
                    set<Estado*> transicao_B = (*B)->getTransicao(*a);
                    transicao_A.insert(transicao_B.begin(), transicao_B.end()); //nova transição para um conjunto de estados a partir de cada um dos estados que A representa
                }
                for(auto C = transicao_A.begin(); C != transicao_A.end();C++){//para cada estado que pode ser alcançado pelos estados que A representa
                    transicao_novo.insert(fecho.map[*C].begin(), fecho.map[*C].end()); //nova transição para um conjunto de estados a partir de cada um dos estados
                }
                for(auto D = estados_determinizados.map.begin(); D != estados_determinizados.map.end();D++){ //para cada estado já existente no automato, verificar se o novo já existe.
                    if(D->second==transicao_novo){//o estado destino já existe.
                        flag_novo = false;
                        (*A)->insereTransicao(*a, D->first);
                    }
                }
                if(flag_novo){
                    Estado novo2;
                    estados_determinizados.map.insert({&novo2,transicao_novo});
                    (*A)->insereTransicao(*a, &novo2);
                    novo_det_temp.insert(&novo2);
                }
            }
        }
        novo_em_det = novo_det_temp;
    }
    Automato deterministico;
    deterministico.q0 = novo;
    deterministico.alfabeto = alfabeto;
    set<Estado> finais, estados;
    for(auto A = estados_determinizados.map.begin(); A != estados_determinizados.map.end();A++){ //para cada estado do automato
        estados.insert(*(A->first));
        for(auto B = A->second.begin(); B != A->second.end();B++){//para cada estado que A representa
            for(auto F = _finais.begin(); F != _finais.end();F++){//para cada estado final do atual
                Estado x = *(*B);
                Estado y = *F;
                if(&x == &y){
                    finais.insert(*(A->first));
                }
            }
        }
    }
    deterministico._estados = estados;
    deterministico._finais = finais;
    return deterministico;
}

/*
Automato Automato::getMinimo();*/
