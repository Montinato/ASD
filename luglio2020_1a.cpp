#include"GrafoPesato.hpp"
#include<iostream>
using namespace std;

bool condizione(int nodo,GrafoPesato& G)
{
    int sommaPesiArchiUscenti = 0;
    vector<int> pesiNodiAdiacenti;
    vector<int> adiacenti;

    for(int i=0;i<G.n();i++)
    {
        if(G(nodo,i))
        {
            adiacenti.push_back(i);
            sommaPesiArchiUscenti += G.w(nodo,i);
        }
    }

    cout<<"La somma dei pesi degli archi uscenti dal nodo "<<nodo<<" e': "<<sommaPesiArchiUscenti<<endl;

    for(int j=0;j<adiacenti.size();j++)
    {
        for(int i=0;i<G.n();i++)
        {
            if(adiacenti[j],i)
            {
                pesiNodiAdiacenti.push_back(G.w(adiacenti[j],i));
            }
        }
    }   

    for(int i=0;i<pesiNodiAdiacenti.size();i++)
    {
        if(sommaPesiArchiUscenti < pesiNodiAdiacenti[i])
            return false;
    }

    return true;
}

int main()
{
    GrafoPesato G(5);
    G(0,1,true,2);
    G(0,2,true,4);
    G(0,3,true,8);
    G(1,4,true,6);
    G(3,4,true,5);
    G(4,2,true,4);


    bool cond = true;

    for(int i=0;i<G.n();i++)
    {
        if(!condizione(i,G))
        {
            cond = false;
            break;
        }
    }

    if(cond)
        cout<<"SIUUU";
    else
        cout<<"NO";

    return 0;
}