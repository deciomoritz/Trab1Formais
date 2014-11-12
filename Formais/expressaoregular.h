#ifndef EXPRESSAOREGULAR_H
#define EXPRESSAOREGULAR_H

#include "automato.h"

# include <stdio.h>

# include <string.h>
# include <ctype.h>

#include <vector>
#include <unordered_map>

#include <iostream>

#include <stack>

using namespace std;

const char concatenacao = 234;
//const char concatenacao = '.';

/*! \brief Enumeração usada para relacionar uma operação com um char representando a operação
 *
 */
enum Operador{
    Concatenacao = concatenacao, Uniao = '|', Fechamento = '*', Opcional = '?'
};

class ExpressaoRegular
{
    void _ERParaAFND(int st,int p,char *s);

    std::vector<int> ret;
    int pos;
    int sc;

public:
    /*! \brief Construtor vazio, padrão
     *
     */
    ExpressaoRegular();

    /*! \brief Retorna AF gerado a partir da expressão regular ER
     *
     *  \param string ER
     */
    Automato ERParaAFND(string ER);

    /*! \brief Usado por ERParaAFND(string ER), retorna AFND gerado a partir de ER
     *
     *  \param string ER
     */
    Automato _ERParaAFND(string er);

    /*! \brief Efetua tratamento prévio na string lida
     *
     *  \param char * er string representando er regular seguindo padrão visto em aula
     */
    string preProcessar(char * er);

    /*! \brief Retorna o AFND correspondente à concatenação de todos os simbolos da entrada
     *
     *  \param string de simbolos a serem concatenados
     */
    Automato concatena(string simbolos);
    /*! \brief Retorna subexpressão(string), sendo basicamente a expressão passada como parâmetro sem parenteses
     *
     *  \param string expressão
     */
    string subExpressao(string expressao);
};

#endif // EXPRESSAOREGULAR_H
