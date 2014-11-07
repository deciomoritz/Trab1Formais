#ifndef ESTADO_H
#define ESTADO_H
#include <algorithm>
#include <string>
using std::string;
#include <unordered_map>
using std::unordered_map;
#include <set>
using std::set;

typedef char Simbolo;

class Estado
{
    string _nome;
    unordered_map<Simbolo,set<Estado*>> _delta; //estrutura que mapeia um Simbolo(char) para um ConjuntoDeEstados
public:

    Estado();
    Estado(Simbolo nome);
    Estado(string nome, unordered_map<Simbolo, set<Estado*>> delta);
    set<Estado*> fecho();
    string nome() const;
    set<Estado*> getTransicao(Simbolo s) const;

    bool operator<(const Estado& e) const{
       return _nome<e._nome;
    }

    bool operator==(const Estado& e) const{
       return _nome==e._nome;
    }
    Estado(set<Estado*> estados);

    void insereTransicao(Simbolo s, Estado * q);
};

#endif // ESTADO_H
