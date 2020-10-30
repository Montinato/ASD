#ifndef GRAFO_H_
#define GRAFO_H_

#include <cassert>
#include <vector>

// Equivale ad usare un typedef ( assegnare dei nomi alternativi a dei tipi di dato esistenti )
using boolVec = std::vector<bool>;

// Grafo orientato in cui i nodi sono degli interi 
class Grafo 
{
    protected:
    
    // numero di nodi, numero di archi
    unsigned vn = 0, vm = 0; 
    
    // matrice di adiacenza

    // Nella cella i,j  c'è il valore TRUE se l'arco i,j è collegato.
    std::vector<boolVec> archi; 

    // inizializza la matrice di adiacenza
    void init(unsigned n) {
        this->vn = n;
        this->vm = 0;

        this->archi = std::vector<boolVec>(n);
        for (unsigned i = 0; i < n; i++)
            this->archi[i] = boolVec(n, false);
    }

public:

    // Grafo con n nodi indicizzati da 0 a n-1
    Grafo(unsigned n) {
        assert(n >= 1);
        this->init(n);
    }

    // inserisce o elimina l'arco (i,j) (a seconda del valore di b)
    // Ridefinizione dell'operatore ()
    // Grafo G(i,j,true) -> INSERISCI UN ARCO che va da i a j
    // Grafo ((i,j,false) -> Se esiste ELMINA questo arco
    void operator()(unsigned i, unsigned j, bool b) {
        assert(i >= 0 && i < this->n() && j >= 0 && j < this->n());
        bool esisteArco = this->archi[i][j];
        if ((!esisteArco && b) || (esisteArco && !b)) {
            this->archi[i][j] = b;  // arco i->j
            if (b)
                vm++;   // Aumento il numero di archi 
            else
                vm--;   // Decremento il numero di archi 
        }
    }

    // elimina tutti gli archi
    void svuota() {
        for (unsigned i = 0; i < this->n(); i++)
            for (unsigned j = 0; j < this->n(); j++)
                archi[i][j] = false;
        vm = 0;
    }

    Grafo& operator=(const Grafo& g) {
        if (this == &g)
            return *this;
        this->init(g.n());
        for (unsigned i = 0; i < this->n(); i++)
            for (unsigned j = 0; j < this->n(); j++)
                if (g(i,j))
                    this->archi[i][j] = true;
                else
                    this->archi[i][j] = false;
        return *this;
    }

    
    unsigned n() const { return vn; }   // Restituisce il numero di nodi 
    unsigned m() const { return vm; }   // Restituisce il numero di archi 
    
    // Altra implementazione dell'operatore() che questa volta riceve 2 parametri 
    // Restituisce true se l'arco (i,j) esiste, altrimenti false
    bool operator()(unsigned i, unsigned j) const {
        assert(i >= 0 && i < this->n() && j >= 0 && j < this->n());
        return this->archi[i][j];
    }
};

#endif