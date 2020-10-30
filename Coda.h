// Coda.h: the Coda template class.
//
//////////////////////////////////////////////////////////////////////

#ifndef CODA_H
#define CODA_H

#include "Lista.h"
#include <assert.h>

template< class T >
class Coda : private Lista<T>
{
public:
    Coda() {};
    
    void inCoda( const T &value ) { addInCoda(value); };
    
	T fuoriCoda() {
        assert(!vuota());
        T temp=Lista< T >::valInTesta();
        Lista<T>::delInTesta();
        return temp;
    };
    
	bool vuota() { return (Lista< T >::testa == NULL); };
};

#endif
