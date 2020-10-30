// Lista.h: the Lista template class.
//
//////////////////////////////////////////////////////////////////////

#ifndef LISTA_H
#define LISTA_H

#include "Nodo.h"
#include <assert.h>

template <class T>
class Lista
{ 
public :     
    Lista<T>():testa(0),coda(0){};
    
	~Lista<T>() {
        if(testa == 0) return;
        while(testa != coda) {
            Nodo<T> * tmp = testa;
            testa = testa->getNextNodo();
            delete tmp;
        }
        delete testa;
    };
    
    Nodo<T>* getTesta() const { return testa; };
    
    Nodo<T>* getCoda() const { return coda; };
    
	void addInTesta(T i) {
        Nodo<T> * tmp = testa;
        testa = new Nodo<T>(i, tmp);
        if (coda == 0) 
            coda = testa;
    };
    
	void addInCoda(T i) {
        Nodo<T>* tmp = coda;
        coda = new Nodo<T>(i,0);
        if (testa == 0) 
            testa = coda;
        else 
            tmp->setNextNodo(coda);
    };
    
	Nodo<T>* cerca(T i) const {
        Nodo<T>* tmp = testa;        
        while(tmp != 0) {
            if(tmp->getValore() == i) break;
            tmp = tmp->getNextNodo();
        }           
        return tmp;
    };
    
	T valInTesta() const {
        assert(testa!=0);
        return testa->getValore();
    };
    
	T valInCoda() const {
        assert(coda!=0);
        return coda->getValore();
    };
    
	void delInTesta() {
        if(testa == 0) 
            return;
        Nodo<T>* tmp = testa;
        testa = tmp->getNextNodo();
        delete tmp;
    };
    
	void delInCoda() {
        if(testa == coda) {
            delInTesta();
            return;
        }
        Nodo<T> * corr = testa;
        Nodo<T> * prec = 0;
        while (corr != coda) {
            prec = corr;
            corr = corr->getNextNodo();
        }
        prec->setNextNodo(0);
        delete coda;
        coda = prec;
    };
    
	void cancellaTutti(T i) {
        if (testa == 0) return;
        Nodo<T> * corr = testa;
        Nodo<T> * prec = 0;
        while (corr != 0)
            if (corr->getValore() == i) {
                Nodo<T> * tmpCorr = corr;
                corr = corr->getNextNodo();
                cancellaNodo(tmpCorr, prec);
            }
            else {
                prec = corr;
                corr = corr->getNextNodo();
            }
    };
    
    void cancellaNodo(Nodo<T> * daElim, Nodo<T> * prec) {
        if (daElim == testa) {
            testa = daElim->getNextNodo();
            if (daElim == coda)
                coda = 0;
        } 
        else {   
            if (daElim == coda)
                coda = prec;
            prec->setNextNodo(daElim->getNextNodo());
        }
        delete daElim;
    };
    
	void svuota() {
        while (testa != 0) 
            delInTesta();
    };
    
protected:
	Nodo<T> * testa;
	Nodo<T> * coda;
};

template<class T>
ostream& operator<<(ostream& out, const Lista<T>& l)
{
    Nodo<T> * tmp = l.getTesta();
    while(tmp != 0)
    {
        out << *tmp <<endl;
        tmp = tmp->getNextNodo();
    }
    return out;
}

#endif
