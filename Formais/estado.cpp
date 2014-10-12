#include "estado.h"

Estado::Estado()
{
    _nome = "";
    _tipo = Intermediario;
}

Estado::Estado(string nome, Tipo tipo){
    _nome = nome;
    _tipo = tipo;
}

string Estado::nome(){
    return _nome;
}
