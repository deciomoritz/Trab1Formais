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
public:
    string _nome;
    unordered_map<string,set<Estado*>> _delta; //estrutura que mapeia um Simbolo(char) para um ConjuntoDeEstados

    Estado();
    Estado(string nome);
    Estado(string nome, unordered_map<string, set<Estado*>> delta);
    set<Estado*> fecho();
    string nome() const;
    set<Estado*> getTransicao(string s) ;

    bool operator<(const Estado& e) const{
       /*cout << this->nome();
       cout << " < " << e.nome() ;
       cout << " = " <<(this->nome().compare(e.nome())<0) << endl;*/
       return _nome.compare(e._nome)<0;
    }
    Estado(set<Estado*> estados);

    void insereTransicao(Simbolo s, Estado * q);
};
//struct less_pointer
//{
//    bool operator()(Estado* const& lhs, Estado* const& rhs)
//    {
//        return lhs->nome().compare(rhs->nome())<0;
//    }
//};
#endif // ESTADO_H
