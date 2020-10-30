#include"Grafo.h"
#include"FunzioniGrafo.h"
#include<vector>
#include<iostream>
using namespace std;

bool canAdd(int x,vector<pair<int,int>>& V,Grafo& G,Grafo& G1,int k)
{
    cout<<"METODO canAdd: "<<endl;

    cout<<"In G ci sono: "<<endl;
    FunzioniGrafo F;
    F.stampa(G);

    cout<<"Mentre in G1 ci sono: "<<endl;
    F.stampa(G1);

    cout<<"Controllo che l'arco che voglio inserire non esista gia' in G1"<<endl;
    for(int i=1;i<=G1.m();i++)
    {
        if(G1(V[x].first,V[x].second))
            return false;
    }

    cout<<"Se non e' stato inserito lo aggiungo! "<<endl;
    return G1.m() < k;
}

void add(int x,Grafo& G,Grafo& G1,vector<pair<int,int>>& V)
{
    cout<<"METODO Add: "<<endl;

    cout<<"Elimino da G ed aggiungo in G1 "<<V[x].first<<" "<<V[x].second<<endl;

    G(V[x].first,V[x].second,false);
    G1(V[x].first,V[x].second,true);
}

void remove(int x,Grafo& G,Grafo& G1,vector<pair<int,int>>& V)
{
    cout<<"METODO remove: "<<endl;

    cout<<"Questa volta elimino da G1 ed aggiungo in G "<<V[x].first<<" "<<V[x].second<<endl;

    G(V[x].first,V[x].second,true);
    G1(V[x].first,V[x].second,false);
}

bool isComplete(vector<pair<int,int>>& V,Grafo& G,Grafo& G1,int k)
{
    cout<<"METODO isComplete: "<<endl;

    FunzioniGrafo F;
    if(!F.esisteCicloDaTre(G) && !F.esisteCicloDaTre(G1))
    {
        cout<<"Se non ci sono cicli da 3 in G ed in G1 e ci sono almeno k=4 archi restituisco true"<<endl;
        return G.m() == k && G1.m() == k;
    }

    return false;
}

bool bt(Grafo& G,Grafo& G1,vector<pair<int,int>>& V,int k)
{
    int x = 0;

    while(x < V.size())
    {
        if(canAdd(x,V,G,G1,k))
        {
            add(x,G,G1,V);

            if(isComplete(V,G,G1,k))    return true;
            else if(bt(G,G1,V,k))       return true;

            remove(x,G,G1,V);
            x++;
        }
        else    
            x++;
    }

    return false;
}

int main()
{
    int Z,p,k;

    cin>>Z>>p>>k;

    Grafo G(Z);

    int a,b;
    char c;

    vector<pair<int,int>> V;

    for(int i=0;i<p;i++)
    {
        cin>>a>>c>>b;

        G(a,b,true);
        /*  if(G(a,b))
            cout<<"In G e' presente l'arco: "<<a<<","<<b<<endl; */

        V.push_back(pair<int,int> (a,b));
    }

    Grafo G1(Z);
   
    if(bt(G,G1,V,k))
    {
        cout<<"SI"<<endl;
        FunzioniGrafo F;
        cout<<"In G sono presenti: "<<endl;
        F.stampa(G);
        cout<<endl<<"Mentre in G1 sono presenti: "<<endl;
        F.stampa(G1);
    }
    else
        cout<<"NO"<<endl;


    return 0;
}