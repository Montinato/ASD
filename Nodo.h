// Nodo.h: the Nodo template class.
//
//////////////////////////////////////////////////////////////////////

#ifndef NODO_H
#define NODO_H

#include <iostream>
using namespace std;

template <class T>
class Nodo  
{
public:
    Nodo(T i): next(0), valore(i){};
    Nodo(T i, Nodo<T>* n): next(n), valore(i){};
    
    T getValore() const { return valore; };
    void setValore(T i) { valore=i; };
    
    Nodo<T>* getNextNodo() const { return next; };
    void setNextNodo(Nodo<T>* n) { next=n; };
    
private:
	Nodo<T>* next;
	T valore;
};

template<class T>
ostream& operator<<(ostream& out, const Nodo<T>& n)
{
    out << n.getValore();
    return out;
}

#endif
