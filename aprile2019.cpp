#include<iostream>
#include<queue>
#include<vector>
#include"Grafo.h"
#include"FunzioniGrafo.h"
using namespace std;

void add(int x,vector<int>& sol)    { cout<<"METODO add: aggiungo "<<x<<endl; sol.push_back(x); }
void remove(vector<int>& sol) { cout<<"METODO remove: "<<endl; sol.pop_back(); }

bool controllo(int i,const Grafo& G,vector<int>& sol)
{
    cout<<"METODO controllo: "<<endl;
    Grafo G1 = G.n();
    bool check1 = false;
    FunzioniGrafo F;

    for(int j=1;j<=G.n();j++)
    {
        for(int k=1;k<=G.n();k++)
        {
            if(G(j,k))                      // Controllo se l'arco esiste 
            {
                for(int l=0;l<sol.size();l++)            
                    if(sol[l] == j || sol[l] == k) 
                    {
                        cout<<j<<" oppure "<<k<<" fanno parte di sol, non faccio niente"<<endl;              
                        check1 = true;          // Se i nodi fanno parte di sol Ok, vado avanti
                    }

                if(!check1)
                {
                    // Se non fanno parte di sol li aggiungo a G1
                    // In G1 ci saranno i nodi che non sono in sol ma sono collegati
                    cout<<"Il nodo "<<j<<" o il nodo "<<k<<" non fanno parte della sol, aggiungo l'arco a G1"<<endl;
                    G1(j,k,true);
                }

                check1 = false;
            }
        }
    }

    vector<int> nodiCollegati;

    for(int k=1;k<=G1.n();k++)
        if(F.esisteCammino(i,k,G1) && i!=k)             // Controllo se esiste un cammino tra il nodo di sol ed i nodi di G1
            nodiCollegati.push_back(k);

    cout<<"Controllo se esiste un cammino tra "<<i<<" ed i nodi presenti in G1"<<endl;
    cout<<"Se esiste, salvo i nodi in un vector, che stampo qui: "<<endl;
    
    for(int i=0;i<nodiCollegati.size();i++)
        cout<<nodiCollegati[i]<<" ";
    cout<<endl;

    cout<<"Controllo se esiste un cammino tra i nodi collegati ed "<<i<<" , se esiste ruol dire che il nodo "<<i<<" puo' essere raggiunto"<<endl;


    for(int k=0;k<nodiCollegati.size();k++)
    {
        if(F.esisteCammino(nodiCollegati[k],i,G1))
        {
            nodiCollegati.clear();
            cout<<"Il nodo puo' essere raggiunto!"<<endl;
            return true;
        }
    }

    cout<<"Il nodo non puo' essere raggiunto!"<<endl;
    return false;
}

bool isComplete(const Grafo& G,vector<int>& sol,int k)
{
    cout<<"METODO isComplete: "<<endl;

    cout<<"Se la soluzione non e' completa, partendo da cio' che e' presente in sol inizio a controllare"<<endl;

    bool check = false;

    for(int i=1;i<=G.n();i++)
    {
        for(int j=0;j<sol.size();j++)
        {
            if(sol[j] == i)
            {
                cout<<i<<" fa parte della sol non faccio nulla"<<endl;
                check = true;       // Se fa parte della sol e' OK
            }
        }

       
        if(!check)      // Altrimenti controllo se può essere raggiunto
        {   
            cout<<i<<" non fa parte della soluzione uso il metodo controllo()"<<endl;
            if(controllo(i,G,sol))
                return false;       // Se puo' essere raggiunto non lo inserisco
        }
        check = false;     
    }


      if(sol.size() == k)
    {
        cout<<"sol.size() e' uguale a k: "<<sol.size()<<" "<<k<<endl;
        return true;  
    }

}


bool canAdd(int x,const Grafo& G,vector<int>& sol,int k)
{
    cout<<"METODO canAdd: "<<endl;

    if(sol.empty())
    {
        cout<<"sol e' posso aggiungere "<<x<<endl;
        return true;
    }
        
    for(int s : sol)
        if( s == x )
        {
            cout<<x<<" e' presente in sol non posso aggiungerlo"<<endl;
            return false;
        }

    cout<<"Controllo che la size di sol sia minore di k: "<<sol.size()<<" - "<<k<<endl;
    return sol.size() < k; 
}

bool bt(const Grafo& G,vector<int>& sol,int k,int N)
{
    int x = 1;

    while ( x <= N)
    {

        if(canAdd(x,G,sol,k))
        {
            add(x,sol);

            if(isComplete(G,sol,k)) return true;
            else if(bt(G,sol,k,N))  return true;

            remove(sol);
            x++;
        }
        else
            x++;
    }

    return false;
}

int main()
{
    int N,z;

    cin>>N>>z;

    Grafo G(N);

    int x,y;
    char c;

    for(int i=0;i<=12;i++)
    {
        cin>>x;
        
        if(x==-1)
            break;
        
        cin>>c>>y;

        G(x,y,true);
    }

    vector<int> sol;

    if(bt(G,sol,z,N))
    {
        cout<<"SI"<<endl;
        for(int i=0;i<sol.size();i++)
            cout<<sol[i]<<" ";
        cout<<endl;
    }
    else    
        cout<<"NO";

    return 0;
}
