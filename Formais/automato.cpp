#include "automato.h"
void Automato::print(Automato af){
    set<Estado*> K = af.getEstados();
    set<Estado*> finais = af.getFinais();
    set<string> alfabeto = af.getAlfabeto();
    alfabeto.insert("&");
    Estado *inicial = af.getInicial();
    //inicial
    cout << "================= " << endl;
    cout << "INICIAL: " << inicial->nome() << endl;
    //transições
    cout << "TRANSIÇÕES: " << endl;
    for(auto A = K.begin(); A != K.end();A++){
        for(auto a = alfabeto.begin(); a != alfabeto.end();a++){
            string s = *a;
            Estado* e = *A;
            set<Estado*> transicoes = e->getTransicao(s);
            if(!transicoes.empty()){
                for(auto B = transicoes.begin(); B != transicoes.end();B++){
                    cout << (*A)->nome() <<",  "<< *a <<" -> " <<  (*B)->nome() << endl;
                }
            }
        }
    }
    //Finais
    cout << "FINAIS: " << endl;
    for(auto F = finais.begin(); F != finais.end();F++){
        cout << (*F)->nome() << endl;
    }
    cout << "================= " << endl;
}
Automato::Automato(){}
void Automato::deletar(){
       for(auto A = _estados.begin(); A != _estados.end();A++){
           delete *A;
       }
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

bool Automato::verifica_sentenca(string s){
        Automato maq = this->determinizar();
        Estado *atual,*proximo;
        set<Estado*> temp;
        proximo = maq.q0;
        for(int i = 0;i<s.length();i++){\
                atual = proximo;
                string entrada = string(1,s[i]);

                temp = atual->getTransicao(entrada);
                proximo = *(temp.begin());
        }
        bool retorno = maq._finais.find(proximo)!=maq._finais.end();
        maq.deletar();
        return retorno;
}

set<string> Automato::listar_sentencas(int n){
    Automato maq = this->determinizar();
    set<string> sentencas, sentencas_validas, temp;

    if(n ==0){
        if(maq._finais.find(maq.q0)!= maq._finais.end())
            sentencas_validas.insert("&");
        maq.deletar();
        return sentencas_validas;
    }
    sentencas.insert(alfabeto.begin(), alfabeto.end());
    for(int i =1; i<n; i++){
        temp.clear();
        for(auto a = sentencas.begin(); a!= sentencas.end(); a++){
            for(auto b = alfabeto.begin(); b != alfabeto.end();b++){
                string nova = (*a)+(*b);
                temp.insert(nova);
            }
        }
        sentencas.insert(temp.begin(),temp.end());
    }
    for(auto a = sentencas.begin(); a!= sentencas.end(); a++){
        if(a->length() == n){
            if(maq.verifica_sentenca(*a)){
                sentencas_validas.insert(*a);
            }
        }

    }
    maq.deletar();
    return sentencas_validas;
}

Automato Automato::minimizar(){
    Automato maq= this->determinizar();
    print(maq);
    set<Estado*> finais = maq._finais;

    set<Estado*> nFinais = maq._estados;
    for(auto iter = finais.begin(); iter != finais.end();iter++){
        Estado * e = *iter;
        nFinais.erase(e);
    }
    //criar duas classes de equivalencia iniciais

    set<set<Estado*>> classesDeEquivalencia;
    set<set<Estado*>> novoClassesDeEquivalencia;
    novoClassesDeEquivalencia.insert(finais);
    novoClassesDeEquivalencia.insert(nFinais);

    do{
        classesDeEquivalencia = novoClassesDeEquivalencia;
        bool nova_classe_G;
        for(auto iter = novoClassesDeEquivalencia.begin(); iter != novoClassesDeEquivalencia.end();iter++){
            nova_classe_G = false;
            set<Estado*> *classe = &(*iter);
            Estado * a = *((*classe).begin());
            for(auto iter3 = (*classe).begin(); iter3 != (*classe).end();iter3++){//comparar 'a' com todos os elementos desta classe
                Estado * b = *iter3;
                if(a == b)
                    continue;
                if(pertenceAClasseDeEquivalencia(classesDeEquivalencia, a, b))
                    continue;
                    //pertence a classe de equivalência;
                 bool nova_classe = true;

                 for(auto iter4 = novoClassesDeEquivalencia.begin(); iter4 != novoClassesDeEquivalencia.end();iter4++){
                     Estado *c = *((*iter4).begin());
                     if((finais.find(c)!=finais.end() && finais.find(b)!=finais.end()) ||(nFinais.find(c)!=nFinais.end() && nFinais.find(b)!=nFinais.end()) ){
                        if(pertenceAClasseDeEquivalencia(novoClassesDeEquivalencia, b, c)){
                            (*iter4).insert(b);
                            (*classe).erase(iter3);
                            iter3 = (*classe).begin();
                            nova_classe = false;
                            break;
                        }
                    }
                 }
                 if(nova_classe){
                    set<Estado*> novaClasse;
                    novaClasse.insert(b);
                    (*classe).erase(iter3);
                    novoClassesDeEquivalencia.insert(novaClasse);
                    iter3 = (*classe).begin();
                 }
                }
           }

    }while(classesDeEquivalencia != novoClassesDeEquivalencia);


    set<Estado*> novos_estados, novos_finais;
    unordered_map<string,set<Estado*>> nome_classe;
    unordered_map<string,Estado*> nome_estado;
    Estado *novoq0;
    for(auto iter = novoClassesDeEquivalencia.begin(); iter != novoClassesDeEquivalencia.end();iter++){
       set<Estado*> temp_set = *iter;
        Estado *temp = *(temp_set.begin());
        Estado *novo = new Estado(temp->nome());
        nome_classe.insert({temp->nome(),*iter });
        nome_estado.insert({temp->nome(),novo});
        novos_estados.insert(novo);

        if(finais.find(temp) != finais.end())
            novos_finais.insert(novo);

        if(temp_set.find(maq.q0) != temp_set.end()){
            novoq0 = novo;
        }
    }
    for(auto iter = novos_estados.begin(); iter != novos_estados.end();iter++){
        Estado *temp = *iter;
        for(auto iter2 = alfabeto.begin(); iter2 != alfabeto.end();iter2++){
            set<Estado*> representacao = nome_classe[(*temp).nome()];
            Estado *primeiro = *(representacao.begin());
            Estado * transicao = *(((*primeiro).getTransicao(*iter2)).begin());
            for(auto iter3 = nome_classe.begin(); iter3 != nome_classe.end();iter3++){ //para cada estado já existente no automato, verificar se o novo já existe.
                set<Estado*> temp2 = iter3->second;
                if(temp2.find(transicao)!=temp2.end()){
                    string destino = iter3->first;
                    (*temp).insereTransicao(*iter2, nome_estado[destino]);
                }
            }
        }

    }

    Automato retorno(novos_estados, alfabeto, novoq0, novos_finais);
    maq.deletar();
    return retorno;

}

bool Automato::pertenceAClasseDeEquivalencia(set<set<Estado*>>classe, Estado * a, Estado * b){
    for(auto iter4 = alfabeto.begin(); iter4 != alfabeto.end();iter4++){//para cada simbolo do alfabeto
        bool trasicao_eq = false;
        Simbolo simbolo = *iter4;
        set<Estado*> _alcancavelA = a->getTransicao(simbolo);
        set<Estado*> _alcancavelB = b->getTransicao(simbolo);
        Estado * alcancavelA = *_alcancavelA.begin(); //esses conjuntos deverão conter só um elemento
        Estado * alcancavelB = *_alcancavelB.begin(); //pois o AF é determinístico
        for(auto iter5 = classe.begin(); iter5 != classe.end(); iter5++){
            bool teste1 = (*iter5).find(alcancavelA) != (*iter5).end();
            bool teste2 = (*iter5).find(alcancavelB) != (*iter5).end();
            if(teste1&&teste2){//uma xor seria melhor...
                trasicao_eq =  true;
                iter5 = --classe.end();
            }
        }
        if(!trasicao_eq)
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
