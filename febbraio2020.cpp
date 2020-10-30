#include"AlberoB.h"
#include<iostream>
#include<string>
using namespace std;
int main()
{
    int n;
    int radice=0,nuova,vecchia,tappo;
    string dir,simbolo;

    Direzione d = SIN;
    Direzione s = DES;

    // INSERISCO IL PRIMO ALBERO , non so perche non funziona
    AlberoB<int> primo(0);
    AlberoB<int> a(2);
    AlberoB<int> b(3);
    AlberoB<int> c(4);
    b.insFiglio(s,c);
    primo.insFiglio(s,a);
    primo.insFiglio(d,b);

    // INSERISCO IL SECONDO ALBERO
    AlberoB<int> secondo(0);
    AlberoB<int> f(1);
    AlberoB<int> e(2);
    f.insFiglio(d,e);
    secondo.insFiglio(s,f);
    

    // INSERISCO IL TERZO ALBERO
    AlberoB<int> terzo(0);
    AlberoB<int> x(3);
    terzo.insFiglio(d,x);
    
    
    cout<<"La profondita' del primo albero e' : "<<profondita(primo)<<endl;
    cout<<"La profondita' del secondo albero e' : "<<profondita(secondo)<<endl;
    cout<<"La profondita' del terzo albero e' : "<<profondita(terzo)<<endl;

    return 0;
}
