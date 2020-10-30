#include"Grafo.h"
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

bool isomorfi(const Grafo& G1,const Grafo& G2)
{
    if( (G1.n() != G2.n()) || (G1.m() != G2.m()) )
        return false;

    vector<int> grafo1;
    vector<int> grafo2;

    for(int i=1;i<=G1.n();i++)
    {
        int cont1 = 0;

        for(int j=1;j<=G1.n();j++)
        {
            if( G1(i,j) || G1(j,i))
                cont1++;
        }
        grafo1.push_back(cont1);
    }

    for(int i=1;i<=G2.n();i++)
    {
        int cont2 = 0;

        for(int j=1;j<=G2.n();j++)
        {
            if(G2(i,j) || G2(j,i))
                cont2++;
        }
        grafo2.push_back(cont2);
    }

    vector<int>::iterator it1_i = grafo1.begin();
    vector<int>::iterator it1_f = grafo1.end();
    
    
    vector<int>::iterator it2_i = grafo2.begin();
    vector<int>::iterator it2_f = grafo2.end();

    sort(it1_i,it1_f);
    sort(it2_i,it2_f);

    for(int i=0;i<grafo1.size();i++)
    {
        if(grafo1[i] != grafo2[i])
            return false;
    }

    return true;
}

int main()
{
    int N1,N2,E1,E2;

    cin>>N1>>N2>>E1>>E2;

    Grafo G1(N1);
    Grafo G2(N2);
    
    int x,y;
    string s;

    for(int i=0;i<E1;i++)
    {
        cin>>x>>s>>y;

        G1(x,y,true);
    }

    for(int i=0;i<E2;i++)
    {
        cin>>x>>s>>y;

        G2(x,y,true);
    }


    if(isomorfi(G1,G2))
        cout<<"SIUUUU"<<endl;
    else
        cout<<"NOOO"<<endl;

    return 0;
}