#include<iostream>
#include<vector>
#include <sstream>
using namespace std;


void add(int x,vector<pair<string,string>>& V,vector<pair<string,string>>& sol)
{
    //cout<<"Metodo add: aggiungo "<<V[x].first<<" "<<V[x].second<<endl;

    sol.push_back(V[x]);
}

void remove(vector<pair<string,string>>& sol)
{
    //cout<<"Metodo remove: rimuovo "<<endl;
    sol.pop_back();
}

bool isComplete(vector<pair<string,string>>& V,vector<vector<int>>& P,vector<pair<string,string>>& sol,int q)
{
    //cout<<"Metodo isComplete, se mi fermo ho trovato la soluzione"<<endl;
    return sol.size() >= q;
}

bool elementoinComune(vector<pair<string,string>>& sol,vector<pair<string,string>>& V,int x)
{
    sol.push_back(V[x]);

    for(int i=0;i<sol.size();i++)
    {
        for(int j=0;j<sol.size() && j!=i;j++)
        {
            if( ((sol[i].first == sol[j].first) || (sol[i].first == sol[j].second))  && ( (sol[i].second == sol[j].second) || (sol[i].second == sol[j].first) ) )
            {
                sol.pop_back();
                return true;
            }
        }
    }

    sol.pop_back();
    return false;
}

bool maxUnaPerOgniInsieme(vector<pair<string,string>>& sol,vector<pair<string,string>>& V,vector<vector<int>>& P,int& x)
{
    sol.push_back(V[x]);

    vector<int> posConv;
    int cont = 0;

    for(int i=0;i<P.size();i++)
    {
        for(int j=0;j<P[i].size();j++)
        {
            posConv.push_back(P[i][j] - 1);     
        }

       /* cout<<"In posConv ho salvato le posizioni da ricercare in V che sono: "<<endl;
        for(int u=0;u<posConv.size();u++)
            cout<<posConv[u]<<" ";
        cout<<endl; */

        for(int k=0;k<posConv.size();k++)
        {
            int a = posConv[k];
            
            for(int m=0;m<sol.size();m++)
            {
                if(V[a] == sol[m])  
                {
                   // cout<<"V[a] = "<<V[a].first<<" "<<V[a].second<<" e'uguale a "<<"sol[m] = "<<sol[m].first<<" "<<sol[m].second<<endl;          
                    cont++;
                   // cout<<"cont = "<<cont<<endl;
                }
            }

            if(cont > 1)
            {
               // cout<<"Cont > 1, restituisco false"<<endl;
                sol.pop_back();
                return false;
            }
        }

        //cout<<"Per l'insieme "<<i<<" ci sono "<<cont<<" elementi"<<endl;
        cont = 0;
        posConv.clear();
    }

    //cout<<"Cont e' al massimo 1, return true"<<endl;
    sol.pop_back();
    return true;
}



bool canAdd(int x,vector<pair<string,string>>& V,vector<vector<int>>& P,vector<pair<string,string>>& sol)
{
    // DEVO FARE IL METODO CAN ADD

    //cout<<"Metodo canAdd "<<endl;

    if(sol.empty())
    {
        //cout<<"La soluzione e' vuota, posso aggiungere"<<endl;
        return true;
    }

    // Non possono esserci in sol due conversazioni che hanno un individuo in comune
    if(elementoinComune(sol,V,x))
    {
        //cout<<"Non posso aggiungere, in sol non ci possono essere conversazioni con individui in comune"<<endl;
        return false;
    }
    

    // sol deve contenere al massimo una sola conversazione da ogni insieme Pi
    if(!maxUnaPerOgniInsieme(sol,V,P,x))
    {
        //cout<<"Ci sono piu' persone per ogni insieme"<<endl;
        return false;
    }

    return true;

}

bool bt(vector<pair<string,string>>& V,vector<vector<int>>& P,vector<pair<string,string>>& sol,int& q)
{
    //cout<<"Metodo bt: "<<endl;
    int x=0;

    while( x < V.size())
    {
        if(canAdd(x,V,P,sol))
        {
            add(x,V,sol);

            if(isComplete(V,P,sol,q))   return true;
            else if(bt(V,P,sol,q))  return true;

            remove(sol);
            x++;
        }
        else
            x++;
    }

    return false;
}

int pos(pair<string,string>& x,vector<pair<string,string>>& V)
{
    for(int i=0;i<V.size();i++)
        if(V[i] == x)
            return i+1;
    return -1;
}

int main()
{
    int n,q,t;

    cin>>n>>q>>t;

    vector<pair<string,string>> V;
    pair<string,string> temp;

    string s1,s2,s3;

    for(int i=0;i<n;i++)
    {
        cin>>s1>>s2>>s3;

        temp.first = s1;
        temp.second = s3;

        V.push_back(temp);
    }

    // VALORI PER IL PRIMO TEST CASE    
    vector<int> T1; T1.push_back(2);    T1.push_back(3);    T1.push_back(4);
    vector<int> T2; T2.push_back(1);    T2.push_back(7);    
    vector<int> T3; T3.push_back(5);
    vector<int> T4; T4.push_back(6);    T4.push_back(8);    

    vector<vector<int>> P;

    P.push_back(T1);
    P.push_back(T2);
    P.push_back(T3);
    P.push_back(T4);

   /* for(int i=0;i<P.size();i++)
    {
        cout<<"Stampo T"<<i+1<<endl;
        for(int j=0;j<P[i].size();j++)
            cout<<P[i][j]<<" ";
        cout<<endl;
    }   */

    vector<pair<string,string>> sol;

    if(bt(V,P,sol,q))
    {
        cout<<"SIUUUUU"<<endl;
        for(int i=0;i<sol.size();i++)
            cout<<pos(sol[i],V)<<" "<<sol[i].first<<" "<<sol[i].second<<endl;
    }
    else
        cout<<"NO";
    
    
    return 0;
}


