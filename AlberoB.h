/*
 * AlberoB.h
 *
 *  Created on: 8 apr 2020
 *      Author: Cesk9
 */

#ifndef ALBEROB_H_
#define ALBEROB_H_

#include <assert.h>
#include<algorithm>
#include<list>


enum Direzione { SIN=0, DES=1 };

template <class T>
struct SNodo
{
	T vinfo; // parte informativa
	SNodo *ppadre, *pfiglio[2]; // puntatori al padre e ai due figli
	SNodo( const T& inf ): vinfo(inf)
	{	ppadre = pfiglio[SIN] = pfiglio[DES] = 0;
	}
	~SNodo( ) {delete pfiglio[SIN]; delete pfiglio[DES];}
};

template <class T>
class AlberoB
{
	protected:
		SNodo<T>* pradice; // puntatore alla radice
	public:
//	FUNZIONI NON COSTANTI
    AlberoB () : pradice(0) {};
    AlberoB ( const T& a) {
        pradice = new SNodo<T>(a);
 };

	//	inserisce l'albero AC come figlio d = SIN/DES
    void insFiglio ( Direzione d, AlberoB& AC ) {
        assert( !nullo() );
        assert( figlio(d).nullo() );
        if ( !AC.nullo() ) {
            pradice->pfiglio[d]=AC.pradice;
            AC.pradice->ppadre=pradice;
        }
    };

	// 	estrae il figlio d = SIN/DES
    AlberoB<T> estraiFiglio ( Direzione d ) {
        assert( !nullo() );
        AlberoB<T> A = figlio(d);
        A.pradice->ppadre=0;
        pradice->pfiglio[d] = 0;
        return A;
    };

    // modifica il contenuto informativo della radice
    void modRadice ( const T& a ) {
        assert( !nullo() );
        pradice->vinfo = a;
    };

	// svuota l'albero cancellandone tutti i nodi
    void svuota() { delete pradice; pradice = 0; };

	// svuota l'albero ma senza cancellare i nodi
    void annulla() { pradice = 0; };

    //	FUNZIONI COSTANTI
	bool nullo() const { return pradice == 0; };

	// restituisce una copia dell'albero
    AlberoB<T> copia () const {
        if ( nullo() ) return AlberoB<T>();
        AlberoB<T> AC(radice());
        AlberoB<T> fs = figlio(SIN).copia();
        AlberoB<T> fd = figlio(DES).copia();
        AC.insFiglio(SIN,fs);
        AC.insFiglio(DES,fd);
        return AC;
    } ;

	//	mostra l'info della radice
    const T& radice () const {
        assert( !nullo() );
        return pradice->vinfo;
    };

	// restituisce true se la radice Ã¨ nodo foglia
    bool foglia () const {
        return !nullo()&&figlio(SIN).nullo()&& figlio(DES).nullo();
    };

	// restituisce il figlio d = SIN/DES
    AlberoB<T> figlio ( Direzione d ) const {
        assert( !nullo() );
        AlberoB<T> AC;
        AC.pradice = pradice->pfiglio[d];
        return AC;
    };

	//	restituisce il padre eventualmente nullo
    AlberoB<T> padre () const {
        assert( !nullo() );
        AlberoB<T> AC;
        AC.pradice = pradice->ppadre;
        return AC;
    };
};


#include<algorithm>
#include<list>

int max(int x,int y)
{
	return x>y;
}

int profondita(AlberoB<int> A)
{
	if(A.nullo())
		return 0;
	else
	{
		int p1=0,p2=0;

		p1 = profondita(A.figlio(SIN));
		p2 = profondita(A.figlio(DES));

		return 1 + max(p1,p2);

	}
	
}

// Versione poco efficiente
bool bilanciato(AlberoB<int> A)
{
	if(A.nullo())
		return true;
	
	return ((abs(profondita(A.figlio(SIN))) - abs(profondita(A.figlio(DES))) <=1) && (bilanciato(A.figlio(SIN)) && bilanciato(A.figlio(DES))));
}

// Versone piu' efficiente

bool bilanciatoProfondo(AlberoB<int> A,int& p)
{
	if(A.nullo())
		return true;
	else
	{
		int p1=0,p2=0;

		bool b1 = bilanciatoProfondo(A.figlio(SIN),p1);
		bool b2 = bilanciatoProfondo(A.figlio(DES),p2);
		p = max(p1,p2) + 1;

		return (b1 && b2 && (abs(p2) - abs(p1) <= 1));
	}
	
}


void visitaInfissa(const AlberoB<int> A,list<int>& L)
{
	if(!A.nullo())
	{
		visitaInfissa(A.figlio(SIN),L);
		L.push_back(A.radice());
		visitaInfissa(A.figlio(DES),L);
	}
}

bool ricerca(AlberoB<int> A,int value)
{
	if(A.nullo())
		return false;
	
	list<int> lista;

	visitaInfissa(A,lista);

	for(auto i=lista.begin();i!=lista.end();i++)
	{
		if((*i) == value)
			return true;
	}

	return false;
}

#endif /* ALBEROB_H_ */
