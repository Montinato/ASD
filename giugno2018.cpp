#include<iostream>
#include"Grafo.h"
#include<vector>
using namespace std;

string stringa(int& x,vector<pair<string,int>>& V)
{
    return V[x-1].first;
}

void add(int x,vector<int>& sol) 
{ 
    //cout<<"Metodo add: aggiungo"<<x<<endl;  
    sol.push_back(x); 
}

void remove(vector<int>& sol)   
{ 
    //cout<<"Metodo remove: rimuovo"<<endl;
    sol.pop_back(); 
}

bool isComplete(vector<int>& sol,Grafo& G)
{
    //cout<<"Se la size di sol e' uguale ai nodi del grafo RETURN TRUE"<<endl;
    return sol.size() == G.n();
}

bool canAdd(int x,vector<int>& sol,Grafo& G)
{

   // cout<<"Metodo canAdd: "<<endl;

    if(sol.empty())
        return true;

    int size = sol.size();

    for(int i=0;i<sol.size();i++)
    {
        if( (G(i+1,size+1) || G(size+1,i+1) ) && ( sol[i] == x) )
        {
          //  cout<<"Controllo se esiste un arco tra "<<i+1<< " e "<< size + 1 <<" e se "<<sol[i]<< " e' uguale a "<<x<<" return false!"<<endl;
            return false;
        }
    }

    return true;
}

bool bt(vector<pair<string,int>>& V,Grafo& G,vector<int>& sol)
{
    int x = 1;

    while ( x <= 3)
    {
      //  cout<<"Metodo bt, x = "<<x<<endl;

        if(canAdd(x,sol,G))
        {
            add(x,sol);

            if(isComplete(sol,G)) return true;
            else if(bt(V,G,sol))    return true;

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
	int c,m;
	cin>>c>>m;

	string s;
	string s1,s2;
	char a;
	
	Grafo G(c);
	vector<pair <string,int> > V;
	pair <string,int> tmp;
	
	
	for(int i=1;i<=c;i++)
	{
		cin>>s;
		tmp.first=s;
		tmp.second=i;

		//cout<<"Ecco temp.first: "<<tmp.first<<endl;
		//cout<<"Ecco temp.second: "<<tmp.second<<endl;
		V.push_back(tmp);
	}
	
    int x=0,y=0;
	
	for(int i=0;i<m;i++)
	{
		cin>>a;
		getline(cin,s1,' ');
		
		getline(cin,s2,')');
		for(int i=0;i<V.size();i++)
		{
			if(V[i].first==s1)
				x=V[i].second;
			
			if(V[i].first==s2)
				y=V[i].second;
		}
		
		G(x,y,true);
        //cout<<"Esiste una scelta "<<stringa(x,V)<<","<<stringa(y,V)<<endl;
	}   // OK INPUT
	
    vector<int> sol;

    if(bt(V,G,sol))
    {
        cout<<"SI"<<endl;
        for(int i=0;i<sol.size();i++)
        {
            if( sol[i] == 1)
                cout<<V[i].first<<" "<<"10:00 - 12:00"<<endl;
            else if( sol[i] == 2)
                cout<<V[i].first<<" "<<"14:00 - 16:00"<<endl;            
            else if( sol[i] ==3)
                cout<<V[i].first<<" "<<"17:00 - 19:00"<<endl;
        }
    }
    else    
        cout<<"NO"<<endl;
	return 0;
}
