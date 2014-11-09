#include "automato.h"

Automato::Automato(){}
void Automato::deletar(){
       for(auto A = _estados.begin(); A != _estados.end();A++){
           delete *A;
       }
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

Automato Automato::complementar(){
    Automato determinizado = this->determinizar();
    set<Estado*> finais = determinizado._estados;

    for(auto iter = finais.begin(); iter != finais.end();iter++){
        Estado * e = *iter;
        if(determinizado._finais.find(e) != determinizado._finais.end())
            finais.erase(e);
    }

    set<Simbolo> alfabeto = this->alfabeto;
    Estado * inicial = determinizado.q0;
    Automato retorno(determinizado._estados, alfabeto, inicial, finais);
    return retorno.determinizar();
}
Automato Automato::uniao(Automato a, Automato b){
    Automato novo_a = a.determinizar();
    Automato novo_b = b.determinizar();
    set<Estado*> new_estados, new_finais, old_finais_a;
    Estado *problem = (*(--(novo_a._estados).end()));
    string name_problem = problem->nome();
    char nome_c = name_problem.c_str()[0];
    string nome;

    Estado *new_q0, *old_q0, *new_final;
    nome = string(1,++nome_c);
    new_q0= new Estado(nome);
    nome = string(1,++nome_c);
    new_final= new Estado(nome);
    old_q0 = novo_a.q0;
    novo_a.q0 = new_q0;
    old_finais_a = novo_a._finais;
    novo_a._estados.insert(new_q0);
    novo_a._estados.insert(new_final);
    novo_a._finais.clear();
    novo_a._finais.insert(new_final);
    for(auto A = novo_b._estados.begin(); A != novo_b._estados.end();A++){
        nome = string(1,++nome_c);
        (*A)->renomear(nome);
        novo_a._estados.insert(*A);
    }
    for(auto A = novo_b._finais.begin(); A != novo_b._finais.end();A++){
        old_finais_a.insert(*A);
    }
    new_q0->insereTransicao("&", old_q0);
    new_q0->insereTransicao("&", novo_b.q0);
    for(auto A = old_finais_a.begin(); A !=old_finais_a.end();A++){
        (*A)->insereTransicao("&", new_final);
    }
    Automato retorno = novo_a.determinizar();
    novo_a.deletar();
    return retorno;
}
Automato Automato::interseccao(Automato a, Automato b){
    Automato compl_a = a.complementar();
    Automato compl_b = b.complementar();
    Automato uniao_complementos= uniao(compl_a,compl_b );
    Automato interseccao = uniao_complementos.complementar();
    Automato retorno = interseccao.determinizar();
    compl_a.deletar();
    compl_b.deletar();
    uniao_complementos.deletar();
    interseccao.deletar();
    return retorno;
}

Automato Automato::diferenca(Automato a, Automato b){
    Automato compl_b = b.complementar();
    Automato inters = interseccao(a, compl_b);
    Automato retorno = inters.determinizar();
    compl_b.deletar();
    inters.deletar();
    return retorno;
}

bool Automato::equivalencia(Automato b){
    Automato dir = diferenca(*this,b);
    Automato esq = diferenca(b,*this);
    set<Estado*> finais;
    finais.insert(dir._finais.begin(),dir._finais.end());
    finais.insert(esq._finais.begin(),esq._finais.end());
    bool retorno = finais.empty();
    dir.deletar();
    esq.deletar();
    return retorno;
}

Automato Automato::minimizar(){
    set<Estado*> finais = _finais;

    set<Estado*> nFinais = _estados;
    for(auto iter = finais.begin(); iter != finais.end();iter++){
        Estado * e = *iter;
        nFinais.erase(e);
    }
    //criar duas classes de equivalencia iniciais

    set<set<Estado*>> classesDeEquivalencia;
    classesDeEquivalencia.insert(finais);
    classesDeEquivalencia.insert(nFinais);

    set<set<Estado*>> novoClassesDeEquivalencia;
    novoClassesDeEquivalencia.insert(finais);
    novoClassesDeEquivalencia.insert(nFinais);

    do{
        for(auto iter = novoClassesDeEquivalencia.begin(); iter != novoClassesDeEquivalencia.end();iter++){
            set<Estado*> classe = *iter;
            for(auto iter2 = classe.begin(); iter2 != classe.end();iter2++){//para cada elemento da classe
                Estado * a = *iter2;
                bool apagueiAlguem = false;
                for(auto iter3 = classe.begin(); iter3 != classe.end();iter3++){//comparar 'a' com todos os elementos desta classe
                    Estado * b = *iter3;

                    if(!pertenceAClasseDeEquivalencia(classe, a, b)){
                        //classe.erase(b);
                        bool bPertenceANgm = true;
                        for(auto iter4 = novoClassesDeEquivalencia.begin(); iter4 != novoClassesDeEquivalencia.end();iter4++){
                            set<Estado*> classe2 = *iter;
                            if(pertenceAClasseDeEquivalencia(classe2, b)){
                                classe2.insert(b);
                                classe.erase(iter3++);//b
                                apagueiAlguem = true;
                                bPertenceANgm = false;
                            }
                        }
                        if(bPertenceANgm){
                            set<Estado*> novaClasse;
                            novaClasse.insert(b);
                            classe.erase(iter3++);//b
                            apagueiAlguem = true;
                            novoClassesDeEquivalencia.insert(novaClasse);
                        }
                    }
                    if(apagueiAlguem)
                        iter2++;
                }
            }
        }
    }while(classesDeEquivalencia != novoClassesDeEquivalencia);
}

bool Automato::pertenceAClasseDeEquivalencia(set<Estado*> classe, Estado * a, Estado * b){
    for(auto iter4 = alfabeto.begin(); iter4 != alfabeto.end();iter4++){//para cada simbolo do alfabeto
        Simbolo simbolo = *iter4;
        set<Estado*> _alcancavelA = a->getTransicao(simbolo);
        set<Estado*> _alcancavelB = b->getTransicao(simbolo);
        Estado * alcancavelA = *_alcancavelA.begin(); //esses conjuntos deverão conter só um elemento
        Estado * alcancavelB = *_alcancavelB.begin(); //pois o AF é determinístico

        if(classe.find(alcancavelA) != classe.end() || classe.find(alcancavelB) != classe.end())
            return false;
    }
    return true;
}

bool Automato::pertenceAClasseDeEquivalencia(set<Estado*> classeDeEquivalencia, Estado * a){
    for(auto iter = classeDeEquivalencia.begin(); iter != classeDeEquivalencia.end();iter++){
        Estado * e = *iter;
        if(!pertenceAClasseDeEquivalencia(classeDeEquivalencia, a, e))
            return false;
    }
    return true;
}

set<Estado*> Automato::getEstados(){return _estados;}

set<Estado*> Automato::getFinais(){return _finais;}

set<Simbolo> Automato::getAlfabeto(){return alfabeto;}

Estado* Automato::getInicial(){return q0;}


/*
Automato Automato::getMinimo();*/
