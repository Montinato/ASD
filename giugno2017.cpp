#include<iostream>
#include<string>
#include<vector>
#include"Grafo.h"
#include"FunzioniGrafo.h"
#include<algorithm>
using namespace std;

int pos(string& s,vector<string>& V)
{
    for(int i=0;i<V.size();i++)
    {
        if(V[i] == s)
            return i+1;
    }

    return -1;
}

bool ciSonoTutte(vector<string>& A,vector<string>& B)
{
    if(A.size() != B.size())
        return false;

    vector<string>::iterator it1 = A.begin();
    vector<string>::iterator it2 = A.end();

    vector<string>::iterator it3 = B.begin();
    vector<string>::iterator it4 = B.end();

    sort(it1,it2);
    sort(it3,it4);

    for(int i=0;i<A.size();i++)
        if(A[i] != B[i])
            return false;

    return true;
}

string pos2(int& x,vector<string>& V)
{
    return V[x-1];
}

void add(int x,vector<string>& V,vector<string>& sol)
{
    sol.push_back(V[x]);
}

void remove(vector<string>& sol)   { sol.pop_back(); }

bool canAdd(int x,vector<string>& V,Grafo& G,vector<string>& sol,int k)
{
    if(sol.empty())
        return true;

    for(int i=0;i<sol.size();i++)
    {
        if(V[x] == sol[i])
            return false;
    }

    return sol.size() + 1 <= k; 
}

bool presente(string& s,vector<string>& V)
{
    if(V.size() == 0)
        return false;
    
    for(auto x : V)
        if(x == s)
            return true;

    return false;
}

bool isComplete(vector<string>& V,Grafo& G,vector<string>& sol,int k)
{
    vector<string> cittaCollegate;

    for(int i=0;i<sol.size();i++)
    {
        for(int j=1;j<=G.n();j++)
        {
            if(!presente(sol[i],cittaCollegate))
                cittaCollegate.push_back(sol[i]);

            string sJ = pos2(j,V);      // Stringa che identifica il nome del nodo j

            if( (G(pos(sol[i],V),j)) && (!presente(sJ,cittaCollegate)))
                cittaCollegate.push_back(sJ);
            else if(G(j,pos(sol[i],V)) && (!presente(sJ,cittaCollegate)))
                cittaCollegate.push_back(sJ);
        }
    }

    if( ciSonoTutte(cittaCollegate,V) && sol.size() <= k)
        return true;

    return false;
}

bool bt(vector<string>& V,Grafo& G,vector<string>& sol,int k)
{
    int x = 0;

    while( x < V.size())
    {
        if(canAdd(x,V,G,sol,k))
        {
            add(x,V,sol);

            if(isComplete(V,G,sol,k))   return true;
            else if(bt(V,G,sol,k))  return true;

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
    int n,k;

    cin>>n>>k;

    string s;
    vector<string> V;
    
    for(int i=0;i<n;i++)
    {
        cin>>s;
        V.push_back(s);
    }

    string c1,c2,simbolo;
    Grafo G(n);

    for(int j=0;j<2;j++)
    {
        cin>>c1>>simbolo>>c2;
        G(pos(c1,V),pos(c2,V),true);

       // cout<<"Arco "<<pos(c1,V)<<" "<<pos(c2,V)<<endl;       //INPUT OK
    }

    vector<string> sol;


    if(bt(V,G,sol,k))
    {
        cout<<"SI"<<endl;
        for(auto a : sol)
            cout<<a<<" ";
        cout<<endl;
    }
    else    
        cout<<"NO"<<endl;


    return 0;
}