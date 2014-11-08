#ifndef EXPRESSAOREGULAR_H
#define EXPRESSAOREGULAR_H

#include "automato.h"

# include <stdio.h>

# include <string.h>
# include <ctype.h>

#include <vector>
#include <unordered_map>

#include <iostream>

using namespace std;

class ExpressaoRegular
{

    void _ERParaAFND(int st,int p,char *s);


    std::vector<int> ret;
    int pos;
    int sc;

public:
    ExpressaoRegular();

    Automato ERParaAFND(string ER);

    string preProcessar(char * er);
};

#endif // EXPRESSAOREGULAR_H
