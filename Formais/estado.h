#ifndef ESTADO_H
#define ESTADO_H
#include <iostream>
using std::cout;
using std::endl;


#include <algorithm>
#include <string>
using std::string;
#include <unordered_map>
using std::unordered_map;
#include <set>
using std::set;

typedef string Simbolo;

class Estado
{
    string _nome;
    unordered_map<string,set<Estado*>> _delta; //estrutura que mapeia um Simbolo(char) para um ConjuntoDeEstados
public:
    /*! \brief Construtor vazio
     *
     */
    Estado();

    /*! \brief Construtor padrão
     *
     * \param string nome
     *
     */
    Estado(string nome);

    /*! \brief Construtor padrão
     *
     * \param string nome
     * \param unordered_map<string
     * \param set<Estado*>> delta
     */
    Estado(string nome, unordered_map<string, set<Estado*>> delta);

    /*! \brief Retorna o &-fecho do estado
     *
     */
    set<Estado*> fecho();

    /*! \brief Retorna o nome do estado
     *
     */
    string nome() const;

    /*! \brief Retorna conjunto de estados para os quais o Estado transita pelo simbolo s
     *
     */
    set<Estado*> getTransicao(string s) ;

    /*! \brief Sobrecarga do operador <, usado na estrutura set
     *
     */
    bool operator<(const Estado& e) const{
       return _nome.compare(e._nome)<0;
    }

    /*! \brief Sobrecarga do operador == usado para simplificar alguns métodos
     *
     */
    bool operator==(const Estado& e) {
        return _nome.compare(e.nome()) == 0;
    }

    Estado(set<Estado*> estados);
    /*! \brief Renomeia o estado, onde o novo nome será a string s
     *
     *  \param string s
     */
    void renomear(string s);
    /*! \brief Insere uma transição pelo Simbolo s para o estado q
     *
     * \param Simbolo s simbolo do alfabeto
     * \param Estado * q ponteiro para estado
     */
    void insereTransicao(Simbolo s, Estado * q);

};


//};
#endif // ESTADO_H
