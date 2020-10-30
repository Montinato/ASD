#include<iostream>
#include<vector>
using namespace std;

bool isComplete(vector<int>& sol,int k)
{
    return sol.size() == k;
}

bool canAdd(int x,const vector<int>& sol,const vector<vector<bool>>& A)
{
    if(sol.empty())
        return true;

    for(int i=0;i<sol.size();i++)
    {
        if(sol[i] == x)
            return false;
    }

    for(int j=0;j<sol.size();j++)
    {
    
        if( (A[sol[j]][x] == false) && (A[x][sol[j]]) == false)
            return true;
    }
}

void add(int x,vector<int>& sol) { sol.push_back(x);   }

void remove(vector<int>& sol)   { sol.pop_back(); }

bool bt(const vector<int>& P,const vector<vector<bool>>& A,vector<int>& sol,int k)
{
    int x = 0;

    while( x < P.size() )
    {
        if(canAdd(P[x],sol,A))
        {
            add(P[x],sol);

            if(isComplete(sol,k)) return true;
            else if(bt(P,A,sol,k))  return true;

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
    vector<int> P;

    P.push_back(0);
    P.push_back(1);
    P.push_back(2);
    P.push_back(3);
    P.push_back(4);

    int k = 3;
    bool x;

    vector<vector<bool>> A(5);


    for(int i=0;i<A.size();i++)
	{
		for(int j=0;j<A.size();j++)
		{
			cin>>x;
			A[i].push_back(x);
        }
    }

    vector<int> sol;


    if(bt(P,A,sol,k))
    {
        cout<<"SIUUUU"<<endl;
        for(int i=0;i<sol.size();i++)
            cout<<sol[i]<<" ";
        cout<<endl;
    }
    else    
        cout<<"OH NO"<<endl;




    cout<<"Stampa del return0!"<<endl;
    return 0;
}