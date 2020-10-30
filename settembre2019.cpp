#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include"Grafo.h"
#include"FunzioniGrafo.h"
using namespace std;

int pos(string& s,vector<string>& V)
{
    for(int i=1;i<=V.size();i++)
        if( s == V[i])
            return i;

    return -1;
}

void add(int& x,vector<pair<string,string>>& V,vector<pair<string,string>>& sol)        {   sol.push_back(V[x]); }

void remove(vector<pair<string,string>>& sol)   {   sol.pop_back(); }

int collegamenti(string x,vector<pair<string,string>>& sol)
{
    int cont = 0;

    for(int i=0;i<sol.size();i++)
    {
        if( (x == sol[i].first) || (x == sol[i].second) )
            cont++;
    }

    return cont;

}

bool isComplete(vector<string>& porti,vector<pair<string,string>>& sol,int& h)
{  

    int coll = 0;
    
    for(int i=0;i<porti.size();i++)
    {
        coll = collegamenti(porti[i],sol);

        if((coll != 0) && ( coll != 3))
            return false;
    }
    
    return sol.size() == h;
}

bool canAdd(int& x,vector<pair<string,string>>& V,vector<pair<string,string>>& sol)
{
    if(sol.empty())
        return true;

    for(int i=0;i<sol.size();i++)
        if(sol[i] == V[x])
            return false;

    return true;
}

bool bt(vector<pair<string,string>>& V,Grafo& G,vector<pair<string,string>>& sol,vector<string>& porti,int h)
{
    int x = 0;

    while( x < V.size() )
    {
        if(canAdd(x,V,sol))
        {
            add(x,V,sol);

            if(isComplete(porti,sol,h)) return true;
            else if(bt(V,G,sol,porti,h))  return true;

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
    int np,nr,h;
    vector<pair<string,string>> V;
    pair<string,string> temp;
    

    cin>>np>>nr>>h;

    vector<string> porti(np);
    Grafo G(np);

    string s1,x,y,s2;

   for(int i=0;i<nr;i++)
    {
        cin>>s1>>x>>y>>s2;

        porti.push_back(x);
        porti.push_back(y);
        

        temp.first = x;
        temp.second = y;
        V.push_back(temp);
    }   

    vector<string>::iterator it = porti.begin();
    vector<string>::iterator it1 = porti.end();

    sort(it,it1);
    unique(it,it1);

    /*  for(int i=1;i<=np;i++)
        cout<<i<<" "<<porti[i]<<" ";
    IL PORTI PARTONO DA 1   */

    for(int i=0;i<V.size();i++)
    {
        G(pos(V[i].first,porti),pos(V[i].second,porti),true);
        G(pos(V[i].second,porti),pos(V[i].first,porti),true);        
    }

    

    /*  int cont = 1;
    for(int i=1;i<=G.n();i++)
    {
        for(int j=1;j<=G.n();j++)
        {
            if(G(i,j))
            {   
                cout<<cont<<" ";
                cout<<"Esiste l'arco "<<i<<" "<<j<<endl;
                cont++;
            }
        }
    }   INPUT OK  */


    vector<pair<string,string>> sol;

    if(bt(V,G,sol,porti,h))
    {
        cout<<"SI"<<endl;
        for(int i=0;i<sol.size();i++)
            cout<<sol[i].first<<" "<<sol[i].second<<endl;
        cout<<endl;
    }
    else
        cout<<"NO"<<endl;


    return 0;
}


/* 
INPUT 1 TEST CASE   SI
6 8 6
[ a b ]
[ b e ]
[ c b ]
[ b d ]
[ c d ]
[ e d ]
[ e c ]
[ e f ]     

INPUT 2 TEST CASE   SI

5 9 6
[ a1 c1 ]
[ a1 b1 ]
[ c1 b1 ]
[ a1 d2 ]
[ b1 d2 ]
[ d2 c1 ]
[ b1 e4 ]
[ d2 e4 ]
[ e4 c1 ]


INPUT 3 TEST CASE   NO
7 5 4
[ a1 b2 ]
[ b2 g7 ]
[ g7 c3 ]
[ d4 e5 ]
[ e5 f6 ]
*/