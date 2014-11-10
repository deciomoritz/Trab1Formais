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
        }
        pos++;
    }
    return novaER;
}

Automato ExpressaoRegular::ERParaAFND(string ER){

    char * writable = new char[ER.size() + 1];
    std::copy(ER.begin(), ER.end(), writable);
    writable[ER.size()] = '\0';

    ER = preProcessar(writable);

    writable = new char[ER.size() + 1];
    std::copy(ER.begin(), ER.end(), writable);
    writable[ER.size()] = '\0';

    _ERParaAFND(1,0,writable);

    delete writable;

    Automato af;

    unordered_map<string, Estado*> nomeParaEstado;

    set<Simbolo> alfabeto;
    Estado *final = new Estado("A");
    for(int i=0;i<pos;i=i+3){
        char c = ret[i] + 64;
        string nome(1,c);

        Estado * e = new Estado(nome);

        if(nome.compare(final->nome()) > 0)
            final = e;

        af.add(e);

        c = ret[i+2] + 64;
        string nome2(1,c);

        e = new Estado(nome2);

        if(nome2.compare(final->nome()) > 0)
            final = e;

        af.add(e);

        string simbolo = string(1,ret[i+1]);
        if(simbolo.compare(string(1,'&')) != 0)
            alfabeto.insert(simbolo);
    }

    set<Estado*> estados = af.getEstados();

    for(auto iterador = estados.begin(); iterador != estados.end();iterador++){
        Estado * e = *iterador;

        nomeParaEstado.insert({e->nome(), e});
    }
    Estado * e;
    for(auto iterador = estados.begin(); iterador != estados.end();iterador++){
        e = (*iterador);

        for(int i=0;i<pos;i=i+3){
            //printf("%d     --%c-->      %d\n",ret[i],ret[i+1],ret[i+2]);
            char c = ret[i+2] + 64;
            string nome(1,c);
            Estado * para = nomeParaEstado.find(nome)->second;

            char c2 = ret[i] + 64;
            string nome2(1,c2);
            if(e->nome().compare(nome2) == 0){
                char simbolo = ret[i+1];
                e->insereTransicao(string(1,simbolo), para);
            }

        }
    }
    Estado * inicial = nomeParaEstado.find("A")->second;

    set<Estado*> finais;
    finais.insert(final);

    return Automato(af.getEstados(), alfabeto, inicial, finais);
}

void ExpressaoRegular::_ERParaAFND(int st,int p,char *s){

    int i,sp,fs[15],fsc=0;
    sp=st;pos=p;sc=st;
    while(*s!=NULL)
    {
        if(isalpha(*s))
        {
            ret[pos++]=sp;
            ret[pos++]=*s;
            ret[pos++]=++sc;
        }
        if(*s==concatenacao)
        {
            sp=sc;
            ret[pos++]=sc;
            ret[pos++]='&';
            ret[pos++]=++sc;
            sp=sc;
        }
        if(*s=='?')
        {
            ret[pos++]=sp;
            ret[pos++]='&';
            ret[pos++]=sc;
        }
        if(*s=='|')
        {
            sp=st;
            fs[fsc++]=sc;
        }
        if(*s=='*')
        {
            ret[pos++]=sc;
            ret[pos++]='&';
            ret[pos++]=sp;
            ret[pos++]=sp;
            ret[pos++]='&';
            ret[pos++]=sc;
        }
        if (*s=='(')
        {
            char ps[50];
            int i=0,flag=1;
            s++;
            while(flag!=0)
            {
                ps[i++]=*s;
                if (*s=='(')
                    flag++;
                if (*s==')')
                    flag--;
                s++;}
            ps[--i]='\0';
            _ERParaAFND(sc,pos,ps);
            s--;
        }
        s++;
    }
    sc++;
    for(i=0;i<fsc;i++)
    {
        ret[pos++]=fs[i];
        ret[pos++]='&';
        ret[pos++]=sc;
    }
    ret[pos++]=sc-1;
    ret[pos++]='&';
    ret[pos++]=sc;

    for (int i = 0; i < ret.size(); ++i) {
        cout << ret[i] << endl;
    }
}
