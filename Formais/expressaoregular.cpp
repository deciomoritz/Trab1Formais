#include "expressaoregular.h"

ExpressaoRegular::ExpressaoRegular()
{
    ret.reserve(300);
    pos = 0;
    sc = 0;
}

string ExpressaoRegular::preProcessar(char * er){
    int pos = 0;
    char anterior, atual;

    string novaER = er;

    char* str = er;
    for(char* it = str; *it; it++) {
        atual = *it;
        anterior = *(it-1);

        if(anterior != '|' && anterior != '*' && anterior != '(' && anterior != ')' && anterior != NULL && anterior != '?' &&
                atual != '|' && atual != '*' && atual != '(' && atual != ')' && atual != '?' && atual != NULL){
            novaER.insert(pos, 1,concatenacao);
            pos++;
        }else if(anterior == (')') && atual == ('(')){
            novaER.insert(pos, 1,concatenacao);
            pos++;
        }else if(anterior == '*' && atual != NULL && atual != '|' && atual != ')' && atual != '?'){
            novaER.insert(pos, 1,concatenacao);
            pos++;
        }else if(anterior == (')') && atual != NULL && atual != '|' && atual != ')' && atual != '(' && atual != '*' && atual != '?'){
            novaER.insert(pos, 1,concatenacao);
            pos++;
        }else if(anterior == ('?') && atual != NULL && atual != '|' && atual != ')' && atual != '*' && atual != '?'){
            novaER.insert(pos, 1,concatenacao);
            pos++;
        }else if((isalpha(anterior) || isdigit(anterior)) && atual == '('){
            novaER.insert(pos, 1,concatenacao);
            pos++;
        }
        pos++;
    }
    return novaER;
}

Automato ExpressaoRegular::ERParaAFND(string ER){

    char * writable = new char[ER.size() + 1];
    std::copy(ER.begin(), ER.end(), writable);
    writable[ER.size()] = '\0';

    ER = preProcessar(ER.c_str());

    return  _ERParaAFND(ER);
}

Automato ExpressaoRegular::_ERParaAFND(string er){

    stack<Operador> operadores;
    stack<Automato> operandos;

    for(string::iterator it = er.begin(); it != er.end(); ++it) {
        char atual = *it;

        if(atual == Fechamento){
            Automato a = operandos.top();

            operandos.pop();
            operandos.push(Automato::fechamento(a));
        }else if(atual == Opcional){
            Automato a = operandos.top();

            operandos.pop();
            operandos.push(Automato::interrogacao(a));
        }else if(atual == Concatenacao || atual == Uniao || atual == Opcional || atual == '('){
            operadores.push(atual);
        }else{

            if(isalpha(atual) || isdigit(atual)){
                operandos.push(Automato::menor_sentenca(string(1,atual)));
            }else{
                char operadorTopo = operadores.top();
                operadores.pop();

                if(operadorTopo == '('){
                    operadores.pop();
                    continue;
                }

                Automato a, b;

                if(operadorTopo == Concatenacao){
                    a = operandos.top();
                    operandos.pop();
                    b = operandos.top();
                    operandos.pop();

                    Automato resultado = Automato::concatena(b,a);
                    resultado.renomear_estados();
                    operandos.push(resultado);
                }else if(operadorTopo == Uniao){
                    a = operandos.top();
                    operandos.pop();
                    b = operandos.top();
                    operandos.pop();

                    Automato resultado = Automato::uniao_simples(a,b);
                    resultado.renomear_estados();
                    operandos.push(resultado);
                }
                operadores.pop();
            }

        }
    }
    Automato af = operandos.top();
    af.renomear_estados();
    return af;
}

Automato ExpressaoRegular::concatena(string simbolos){

    simbolos = preProcessar(simbolos.c_str());

    stack<Automato> operandos;

    for(string::iterator it = simbolos.begin(); it != simbolos.end(); ++it) {
        char atual = *it;

        if(isalpha(atual) || isdigit(atual)){
            operandos.push(Automato::menor_sentenca(string(1,atual)));
        }
    }

    while(operandos.size() != 1){

        Automato a, b;

        a = operandos.top();
        operandos.pop();
        b = operandos.top();
        operandos.pop();

        Automato resultado = Automato::concatena(b,a);
        resultado.renomear_estados();
        operandos.push(resultado);
    }
    Automato af = operandos.top();
    af.renomear_estados();
    return af;
}

string ExpressaoRegular::subExpressao(string expressao){
    string retorno = "";
    for(string::iterator it = expressao.begin()+1; it != expressao.end()-1; ++it) {
        char atual = *it;

        retorno.append(atual);
    }
    return retorno;
}
