#include"Grafo.h"
#include<vector>
using namespace std;

bool func(Grafo& G)
{
    cout<<"ENTRO IN FUNC"<<endl;
    vector<int> adia;

    for(int i=1;i<=G.n();i++)
    {
        cout<<"Inizio a contare i nodi adiacenti a "<<i<<endl;
        for(int j=1;j<=G.n();j++)
        {
            if(G(i,j))
            {
                cout<<j<<" e' adiacente a "<<i<<endl;
                adia.push_back(j);
            }
        }

        cout<<"Il numero di archi adiacenti a "<<i<<" e' "<<adia.size()<<endl;
    

        int cont = 0;

        cout<<"Adesso conto quanti sono i nodi uscenti dagli archi adiacenti!"<<endl;
        for(int k=0;k<adia.size();k++)
        {
            for(int x=1;x<=G.n();x++)
            {
                if(G(adia[k],x))
                    cont++;
            }
        }
        cout<<"I nodi uscenti dagli archi adiacenti sono: "<<cont<<endl;

        cout<<"I nodi adiacenti a "<<i<<" sono: "<<adia.size()<<" mentre gli archi uscenti dai nodi adiacenti sono: "<<cont<<endl;
        if(cont == adia.size())
            return true;

        adia.clear();

    }

    return false;

}

int main()
{
    Grafo G(6);
    int x,y;

    for(int i=0;i<10;i++)
    {
        cin>>x>>y;

        G(x+1,y+1,true);

        cout<<"Ho creato l'arco: "<<x+1<<" "<<y+1<<endl;
    }


    if(func(G))
        cout<<"SIUUUU";
    else
        cout<<"NO"<<endl;


    return 0;

}