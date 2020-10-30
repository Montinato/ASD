#include "Grafo.h"
#include <limits>
#include <iostream>
#include <vector>
#include <queue> 
#include <set>
#include <map>
#include <algorithm>
#include<list>
using namespace std;

class FunzioniGrafo
{
    public:

    void visitaBFS(const Grafo&, int);    
    void visitaDFS(const Grafo&, int, bool[]);
    void input(Grafo& g);
    void input(Grafo& g, int numeroArchi);
    void stampa(Grafo& g);
    void  copiaeCammino(int i, int j, Grafo& G,list<int>&r);
    bool esisteCammino(int, int, Grafo&);
	int numeroMinimoArchiCammino(int, int, Grafo&);
    vector<int> dijkstra(Grafo&, int, int);
    void costruisciCamminoMinimo(int*, int, int, vector<int>&); //precedenti, partenza, arrivo, cammino (vuoto)
    bool costruisciCammino(const Grafo&, int, int, bool*, vector<int>&);//grafo,partenza,arrivo,visitati, cammino(vuoto)

    bool ciclico(Grafo&);
    bool esisteCicloDaTre(Grafo&);
    bool isomorfi(Grafo&, Grafo&);
    bool cricca(const Grafo&, int, vector<int>&, int);

    Grafo chiusuraTransitiva(Grafo&);
};

    //visita in AMPIEZZA
    void FunzioniGrafo::visitaBFS(const Grafo& G, int v) 
    {
        queue<int> c;
        bool visitati[G.n()+1];

        for(int i=0; i<=G.n(); i++)
            visitati[i] = false;
        
        visitati[v]=true;

        c.push(v);

        while(!c.empty())
        {
            int i=c.front();
            c.pop();
            
            for(int j=1; j<=G.n(); j++)
            {
                if(G(i,j) && !visitati[j])
                {
                    c.push(j);
                    visitati[j]=true;
                }
            }

        }
    }

    //visita in PROFONDITA'
    void visitaDFS(Grafo& G, int v, bool visitato[]) 
    {
        visitato[v]=true;
        
        for(int j=1; j<=G.n(); j++)
        {
            if(G(v,j) && !visitato[j])            
                visitaDFS(G, j, visitato);
        }
    }
    
    void FunzioniGrafo::copiaeCammino(int i,int j,Grafo & g,list<int>&q){
        
    }
    void FunzioniGrafo::input(Grafo& g)
    {
        string input;
        cin.ignore();
        while(getline(cin, input)){
            int pos = input.find(" ");
            int nodoP = atoi(input.substr(0, input.size() - pos).c_str());
            string nuovaStringa = input.substr(pos + 1, input.size() - pos - 1);
            pos = nuovaStringa.find(" ");
            int nodoA = atoi(nuovaStringa.substr(pos + 1, nuovaStringa.size() - pos).c_str());
            g(nodoP, nodoA, true);
        }
    }

    void FunzioniGrafo::input(Grafo& g, int numeroArchi)
    {
        int nodoP, nodoA;
        string inutile;
        for(int i = 0; i < numeroArchi; ++i){
            cin >> nodoP >> inutile >> nodoA;
            g(nodoP, nodoA, true);
        }
    }

    void FunzioniGrafo::stampa(Grafo& g)
    {
        for(int i = 1; i <= g.n(); ++i)
            for(int j = 1; j <= g.n(); ++j)
                if(g(i,j))
                    cout << i << " " << j << endl;
    }

    //verifica se ESISTE un CAMMINO tra il nodo i e il noto j
    bool FunzioniGrafo::esisteCammino(int i, int j, Grafo& G)
    {
        //cout<<"Creo la lista q e l'array bool di visitati"<<endl;
        queue<int> q;
        bool visitati[G.n()+1];

        //cout<<endl;
        //cout<<endl;

        //cout<<"Setto l'array tutto a false;"<<endl;
        for(int i=0; i<=G.n(); i++)
            visitati[i] = false;

        //cout<<endl;
        //cout<<endl;

      //  cout<<"Inserisco il nodo "<<i<<" alla lista e visitati["<<i<<"] diventa true"<<endl;
        q.push(i);
        visitati[i] = true;

       // cout<<endl;
        //cout<<endl;

        //cout<<"Finche' la mia lista non e' vuota : "<<endl;
        //cout<<endl;
        while(!q.empty())
        {
            int x = q.front();
            q.pop();

          //  cout<<"Creo una x ed assegno l'elemento che ho inserito nella lista, quindi "<<x<<endl;
            if(x == j){
               // cout<<"Se la mia x coincide con j che passo alla funzione restituisco true"<<endl;
                return true;
            }
           // cout<<endl;

           // cout<<"Continuo con il for in cui scorro i nodi del mio grafo"<<endl;
         //   cout<<endl;

            /*
                Se esiste un arco tra x e k, i due nodi sono diversi e k non e' stato visitato, aggiungo a q -> k, e faccio visitato[k] = true;
                */
            for(int k = 1; k <= G.n(); k++)
            {
                if(G(x, k) && k != x && !visitati[k])
                {
                   // cout<<"Esiste l'arco "<<x<<","<<k<<" aggiungo "<<k<<" alla lista q e visitati["<<k<<"] = true"<<endl;
                    
                    q.push(k);
                    visitati[k] = true;
                }
            }
           // cout<<endl;
        } 

        return false;
    }
    
	
	//restituisce il numero di archi che si trovano sul cammino MINIMO
	int numeroMinimoArchiCammino(int i, int j, Grafo& G)
    {
        if(!(i <= G.n() && i >= 0 && j <= G.n() && j >= 0)){
            cout << "Errore: Uno dei nodi inseriti non esiste" << endl;
            return -1;
        }

        //cout<<"Creo una queue di pair<int,int>, un vector per vedere quali nodi ho visitato, metto in queue la coppia "<<i<<",0 e in visitati aggiungo i"<<endl;
        queue<pair<int, int> > queue;
        vector<int> visited;
        queue.push(pair<int, int>(i, 0));
        visited.push_back(i);

       // cout<<endl;

        while (!queue.empty())
        {
            //cout<<"Salvo in una variabile chiamata actual il contenuto di queue "<<" e lo rimuovo dalla queue"<<endl;
            pair<int, int> actual = queue.front();
            queue.pop();

           // cout<<endl;

           // cout<<"Se il primo elemento di actual e' uguale a j, restituisco "<<actual.second<<endl;
            if(actual.first == j)
                return actual.second;

            //cout<<endl;
            
            for (int k = 1; k <= G.n(); k++)
            {
               // cout<<"Controllo che esista un arco "<<actual.first<<","<<k<<" ,controllo che "<<k<<" non sia stato visitato"<<endl;

                if(G(actual.first, k) && find(visited.begin(), visited.end(), k) == visited.end()){
                    visited.push_back(k);
                    queue.push(pair<int, int>(k, actual.second + 1));
                   // cout<<"Se questa condizione e' vera, visitato["<<k<<"] = true ed aggiungo in queue ["<<k<<","<<actual.second+1<<"] "<<endl;
                }
                   
                    //cout<<"Altrimenti non faccio nulla"<<endl;
            }

            //cout<<endl;
        }
        return -1;	
    }
    
   /* vector<int> FunzioniGrafo::dijkstra(Grafo& G, int S, int E)
    {
        bool visitati[G.n() + 1];
        int pesi[G.n() + 1];
        int prec[G.n() + 1]; 
        for(int i=0; i<=G.n(); i++)
        {
            visitati[i] = false;
            pesi[i] = __INT_MAX__;
            prec[i] = -1;
        }

        pesi[S] = 0;
        visitati[S] = true;
        prec[S] = S;

        queue<int> daVisitare;
        daVisitare.push(S);
     
        while(!daVisitare.empty())
        {
            int nodoCorrente = daVisitare.front();
            visitati[nodoCorrente] = true;
            daVisitare.pop();

            for(int i=1; i<=G.n(); i++)
            {
                if(G(nodoCorrente, i) && nodoCorrente!=i)
                {
                    if(!visitati[i])
                        daVisitare.push(i);

                    if(G.getCosto(nodoCorrente, i) + pesi[nodoCorrente] < pesi[i])
                    {
                        pesi[i] = G.getCosto(nodoCorrente, i) + pesi[nodoCorrente];
                        prec[i] = nodoCorrente;
                    }
                }
            }
        }

        vector<int> v;
        v.push_back(E);
        int ok = true;
        while(ok)
        {
            if(S == prec[v[0]])
            {
                v.insert(v.begin(), S);
                ok = false;
            }

            else 
                v.insert(v.begin(), prec[v[0]]);
        }


        return v;
    } */

    /*grafo,partenza,arrivo,visitati, cammino(vuoto)*/
    bool FunzioniGrafo::costruisciCammino(const Grafo& g, int S, int E, bool* visitato, vector<int>& cammino)
    {
        if(S == E)
        {
            visitato[E] = true;
            return true;
        }
        else
        {
            visitato[S] = true;
            bool trovato = false;
            for(int j = 1; j <= g.n() && !trovato; j++)
            {
                if(g(S,j) && !visitato[j])
                {
                    cammino.push_back(j);
                    trovato = costruisciCammino(g, j, E, visitato, cammino);
                    if(!trovato)
                        cammino.pop_back();
                }
            }
            return trovato;
        }
    }

    /* DATI : precedenti, partenza, arrivo, cammino (vuoto)
    OSSERVAZIONE:
    NEL VECTOR CAMMINO NON SARÀ PRESENTE IL NODO PARTENZA S, FRONT -> BACK PER IL CAMMINO
    IN QUESTO ALGORITMO SI PRESUPPONE CHE IL CAMMINO ESISTA */   
    void FunzioniGrafo::costruisciCamminoMinimo(int *prec, int S, int E, vector<int> &cammino)
    {
        if(prec[E] == S)
        {
            //cammino.push_back(S);
            cammino.push_back(E);
            return;
        }
        costruisciCamminoMinimo(prec, S, prec[E], cammino);
        cammino.push_back(E);
    }


    //costruisce la CHIUSURA TRANSITIVA di un Grafo
    Grafo FunzioniGrafo::chiusuraTransitiva(Grafo& G)
    {
        Grafo GT=G;
        bool continua=true;
        while(continua)
        {
            continua=false;
            for(int k=1; k<=G.n(); k++)
            {
                for(int i=1; i<=G.n(); i++)
                {
                    for(int j=1; j<=G.n(); j++)
                    {
                        if(!GT(i,j) && GT(i,k) && GT(k,j) && i!=j && j!=k && i!=k)
                        {
                            GT(i, j, true);
                            continua=true;
                        }

                    }
                }
            }
        }
        return GT;
    }


    //verifica se un grafo è CICLICO
    bool FunzioniGrafo::ciclico(Grafo& G)
    {
        for(int i=1; i<=G.n(); i++)
        {
            for(int j=1; j<=G.n(); j++)
            {
                if(i!=j && esisteCammino(i, j, G) && esisteCammino(j, i, G))
                    return true;
            }
        }
        return false;
    }

    //verifice se in un grafo esiste un CICLO TRA 3 NODI
    bool FunzioniGrafo::esisteCicloDaTre(Grafo& G)
    {
        for(int i = 1; i <= G.n(); i++)
        {
            for(int j = 1; j <= G.n(); j++)
            {
                for(int k = 1; k <= G.n(); k++)
                {
                    if(G(i, j) && G(j, k) && G(k, i) && i!=j && i!=k && j!=k)
                        return true;
                }
            }
        }
        return false;
    }

    //fa parte della funzione ISOMORFI
    bool check(Grafo G2, int cont, vector<int> & sol)
    {
        int cont2=0;
        for(int i=1; i<=G2.n(); i++)
        {
            for(int j=1; j<=G2.n(); j++)
            {
                if((G2(i, j) || G2(j, i)) && i!=j)
                    cont2++;
            }
            if(cont2==cont && find(sol.begin(), sol.end(), i)==sol.end())
            {
                sol.push_back(i);
                return true;
            }  
            cont2= 0;
        }
        return false;  

    }

    //verifica se due grafi sono ISOMORFI
    bool FunzioniGrafo::isomorfi(Grafo& G1, Grafo& G2)
    {
        int cont=0;
        vector<int> sol;
        for(int i=1; i<=G1.n(); i++)
        {
            for(int j=1; j<=G1.n(); j++)
            {
                if((G1(i, j) || G1(j, i)) && i!=j)
                    cont++;
            }
            if(!check(G2, cont, sol))
                return false;
            cont = 0;
        }
        return true;
    }

    /* restituisce true se il grafo ha una cricca di cardinalità k
    e i nodi che ne fanno parte saranno in "soluzione"*/
    bool FunzioniGrafo::cricca(const Grafo& g, int S, vector<int> & soluzione, int k)
    {
        S = 1;
        while(S <= g.n())
        {
            bool canAdd = true;
            for(int i = 0; i < soluzione.size(); i++)
            {
                if(!g(soluzione[i],S))
                {
                    canAdd = false;
                    break;
                }
            }

            if(canAdd)
            {
                soluzione.push_back(S);
                if(soluzione.size() == k)
                    return true;

                else if(cricca(g, S, soluzione, k))
                    return true;
                    
                else
                {
                    soluzione.pop_back();
                    S++;
                }
            }
            else
            {
                S++;
            }
            
        }
        return true;
    }

