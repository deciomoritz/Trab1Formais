#ifndef ESTADO_H
#define ESTADO_H

#include <string>
using std::string;

#include <unordered_map>
using std::unordered_map;

#include <vector>
using std::vector;

enum Tipo{Final, Inicial, Intermediario};
typedef char Simbolo;

class Estado;

struct EstadosAdjacentes{
    vector<Estado*> _adj;
};

class Estado
{
    string _nome;
    Tipo _tipo;
    unordered_map<Simbolo, EstadosAdjacentes > _delta; //estrutura que mapeia um Simbolo(char) para um ConjuntoDeEstados

public:

    Estado();
    Estado(string nome, Tipo tipo);

    string nome();
};

#endif // ESTADO_H
