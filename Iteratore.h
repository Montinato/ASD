// Iteratore.h: the Iteratore template class.
//
//////////////////////////////////////////////////////////////////////

#ifndef ITERATORE_H
#define ITERATORE_H

#include "Lista.h"
#include <assert.h>

template <class T>
class Iteratore{
public:
    Iteratore() {
        corr = NULL;
        prec = NULL;
    };
    
	Iteratore(Lista<T> & lista) {   
        l = &lista;
        corr = l->getTesta();
        prec = NULL;
    };
    
	T getCurrentValue() const {
        assert(corr != NULL);
        return corr->getValore();
    };
    
	void setCurrentValue(T val) { 
        assert(corr != NULL);
        corr->setValore(val);
    };
    
    bool isNull() { return (corr == NULL); };
    
    void MoveNext() {
        assert(corr != NULL);
        prec = corr;
        corr = corr->getNextNodo();
    };
    
	void MoveBack() {
        assert(corr != NULL);
        if (corr == l->testa) {
            corr = NULL;
            prec = NULL;
        }
        else {
            Nodo<T> * tmp = corr;
            corr = l->testa;
            prec = NULL;
            while (corr->next != tmp) {
                prec = corr;
                corr = corr->next;
            }
        }
    };
    
	void VaiInTesta() {
        corr = l->getTesta();
        prec = NULL;
    };

	void VaiInCoda() {
        corr = l->testa;
        prec = NULL;
        while (corr != l->coda) {   
            prec = corr;
            corr = corr->next;
        }
    };
    
	void InserisciQui(T val) {
        if (corr == l->testa) {
            l->addInTesta(val);
            corr = l->testa;
            prec = NULL;
        }
        else if (prec == l->coda) {
            l->addInCoda(val);
            corr = l->coda;
        }
        else {
            Nodo<T> * newNodo = new Nodo<T>(val);
            newNodo->next = corr;
            prec->next = newNodo;
            corr = newNodo;
        }
    };
    
	void CancellaCorrente() {
        assert(corr != NULL);
        if (corr == l->testa) {
            l->delInTesta();
            corr = l->testa;
            prec = NULL;
        } 
        else if (corr == l->coda) {
            l->delInCoda();
            prec = l->coda;
            corr = NULL;
        }
        else {
            prec->next = corr->next;
            delete corr;
            corr = prec->next;
        }
    };

	bool operator== (const Iteratore<T> &i) {
        return ((l == i.l) && (prec == i.prec) && (corr == i.corr));
    };
    
    bool operator!= (const Iteratore<T> &i){
        return ((l != i.l) || (prec != i.prec) || (corr != i.corr));
    };

private:
	Nodo<T> * corr;
	Nodo<T> * prec;
	Lista<T> * l;
};

#endif
