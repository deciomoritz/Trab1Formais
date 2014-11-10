#ifndef AUTOMATO_H
#define AUTOMATO_H

#include <set>
using std::set;
#include <vector>
using std::vector;
using std::pair;

#include "estado.h"
struct representacaoDoEstado{
    unordered_map<string, set<Estado*>> map;
};

class Automato
{
    set<Estado*> _estados, _finais;
    Estado* q0;
    set<Simbolo> alfabeto;

public:
    /*! \brief Método usado para exibir uma representação visual do automato em console
     *
     */
    void print(Automato af);
    /*! \brief Método dentro do método listar_sentenca
     *
     */
    bool verifica_sentenca(string s);
    /*! \brief Construtor vazio
     *
     */
    Automato();
    /*! \brief Construtor padrão do Automato.
     *  \param set<Estado*> estados conjunto de estados do automato
     *  \param set<Simbolo> alf conjunto contendo alfabeto
     *  \param Estado *inicial ponteiro para estado inicial
     *  \param set<Estado*> finais conjunto de estados finais
     *
     */
    Automato(set<Estado*> estados, set<Simbolo> alf, Estado *inicial, set<Estado*> finais);
    /*! \brief Usado no método determinizar
     *
     */
    representacaoDoEstado fecho_K();
    /*! \brief Retorna um Automato determinístico equivalente
     *
     */
    Automato determinizar();

    /*! \brief Retorna um Automato onde a linguagem gerada por ele
     * é o complemento da linguagem gerada pelo automato original
     *
     */
    Automato complementar();
    /*! \brief Retorna um Automato onde a linguagem gerada por ele é
     * a união da linguagem gerada por a e b
     *
     * \param Automato a
     * \param Automato b
     *
     */
    static Automato uniao(Automato a, Automato b);
    /*! \brief Retorna um Automato onde a linguagem gerada por ele é
     * a intersecção da linguagem gerada por a e b
     *
     * \param Automato a
     * \param Automato b
     *
     */
    static Automato interseccao(Automato a, Automato b);
    /*! \brief Retorna um Automato onde a linguagem gerada por ele é
     * a diferença da linguagem gerada por a e b
     *
     * \param Automato a
     * \param Automato b
     *
     */
    static Automato diferenca(Automato a, Automato b);
    /*! \brief Retorna verdadeiro se b é equivalente ao Automato executor do método
     *
     * \param Automato b Automato que se deseja verificar equivalencia
     *
     */
    bool equivalencia(Automato b);
    /*! \brief Retorna um set<string> contendo todas as sentenças de tamanho n geradas
     * pelo Automato
     *
     * \param int n
     *
     */
    set<string> listar_sentencas(int n);
    /*! \brief Retorna um Automato mínimo equivalente
     *
     */
    Automato minimizar();
    /*! \brief Returna true se a e b pertencem à classe de equivalencia classe
     *
     * \param set<set<Estado*>> classe Classe que se deseja verificar equivalencia
     * \param Estado * a ponteiro para Estado que se deseja verificar equivalencia
     * \param Estado * b ponteiro para Estado que se deseja verificar equivalencia
     *
     */
    bool pertenceAClasseDeEquivalencia(set<set<Estado*>> classe, Estado * a, Estado * b);

    /*! \brief Desaloca os objetos Estado alocados de forma dinâmica
     *
     */
    void deletar();

    /*! \brief Adiciona o Estado e ao Automato
     *
     * \param Estado e estado que será adicionado
     *
     */
    void add(Estado *e);

    set<string> listar_sentencas();
    /*! \brief Retorna o conjunto de todos os estados do Automato
     *
     */
    set<Estado*> getEstados();
    /*! \brief Retorna o conjunto de estados finais do Automato
     *
     */
    set<Estado*> getFinais();
    /*! \brief Retorna conjunto de Simbolo, representando o alfabeto da linguagem gerada
     * pelo Automato
     *
     */
    set<Simbolo> getAlfabeto();
    /*! \brief Retorna Estado representando estado inicial do automato
     *
     */
    Estado* getInicial();
    };

#endif
