#include<iostream>
#include<string>
#include<vector>
using namespace std;

void add(int x,vector<string>& V,vector<string>& sol)   
{ 
    //cout<<"Metodo add: aggiungo "<<V[x]<<endl;    
    sol.push_back(V[x]); 
}

void remove(vector<string>& sol) 
{ 
    //cout<<"Metodo remove: rimuovo "<<endl;
    sol.pop_back(); 
}


bool func(vector<string>& sol)
{
    string a;
    string b;
    int indice = 0,t=0;

    for(int i=0;i<sol.size()-1;i++)
    {
       a = sol[i];
       b = sol[i+1];

       for(int i=0;i<a.size();i++)
       {
           if( (a[i] != b[i]) && ( t == 0) )
           {
                indice = i;
                t++;
           }

            if( (a[i] != b[i]) && (t>0) && i!=indice)
                return false;
       }
    } 

    return true;
}

bool isComplete(vector<string>& sol,int& q) 
{
    
    //cout<<"Metodo isComplete: "<<endl;  
    
    return (sol.size() == q && func(sol));    
    
}

bool congiunte(string& x,string& y)
{
   // cout<<"Metodo congiunte: "<<endl;

    bool cond = false;
    int cont = 0;
    int indice = 0;

    for(int i=0;i<x.size();i++)
    {
       // cout<<"Controllo che "<<x<<" "<<y<<" differiscano al massimo di 2 lettere"<<endl;
        for(int j=0;j<y.size();j++)
        {
            if(x[i] == y[j])
            {
             //   cout<<"x: "<<x<<" y="<<y<<" "<<x[i]<<" "<<y[j]<<endl;
                cond = true;
                break;
            }
        }

        if(!cond)
        {
            cont++;
            
            if(cont == 2) 
                return false;
           // cout<<x<<" "<<x[i]<<" non e' presente!"<<endl;
            
        }

        cond = false;
        
    }
    
    return true;
}


// Non mi funziona il secondo test case, devo controllare la posizione delle lettere che cambiano.
// Nel primo caso va bene, nel secondo invece no .


bool canAdd(int& x,vector<string>& V,vector<string>& sol)
{
   // cout<<"Metodo canAdd: "<<endl;

    if(sol.empty())
    {
      //  cout<<"sol e' vuoto aggiungo "<<endl;
        return true;
    }

    for(auto elem : sol)
        if(elem == V[x])
        {
       //     cout<<elem<<" e' presente in sol non posso aggiungere! "<<endl;
            return false;
        }

    for(int i=0;i<sol.size();i++)
    {
        if(V[x].size() != sol[i].size())
        {
           // cout<<"Le parole hanno dimensione diversa non posso aggiungere! "<<endl;
            return false;
        }
        
        if(!congiunte(V[x],sol[i]))
        {
           // cout<<"Chiamo congiunte"<<endl;
            return false;
        }
    }

    return true;
}

bool bt(vector<string>& V,vector<string>& sol,int q)
{
    int x=0;

    while(x<V.size())
    {
        if(canAdd(x,V,sol)) 
        {
            add(x,V,sol);

            if(isComplete(sol,q))  return true;
            else if(bt(V,sol,q))    return true;

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
    int n,q;

    cin>>n>>q;

    string val;
    vector<string> V;

    for(int i=0;i<n;i++)
    {
        cin>>val;
        V.push_back(val);
    }

    
    /*  cout<<"Stampa del vector: "<<endl;
    for(auto k : V)
        cout<<k<<" ";
    cout<<endl; */


    vector<string> sol;

    cout<<endl;
    
    if(bt(V,sol,q))
    {
        cout<<"SIUUUUU"<<endl;
        for(int i=0;i<sol.size();i++)
            cout<<sol[i]<<" ";
        cout<<endl;
    }
    else
        cout<<"NO"<<endl;

    return 0;
}