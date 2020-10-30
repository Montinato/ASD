#include<iostream>
#include<vector>
#include <sstream>
using namespace std;

void add(int& x,vector<vector<int>>& T,vector<vector<int>>& sol)
{
    sol.push_back(T[x]);
}

void remove(vector<vector<int>>& sol)
{
    sol.pop_back();
}

bool isComplete(vector<vector<int>>& sol,int& q)
{
    return sol.size() >= q;
}

bool check(int& x,vector<vector<int>>& T,vector<vector<int>>& sol)
{
    // DEVO FINIRE QUESTO METODO 
    sol.push_back(T[x]);

    for(int i=0;i<sol.size();i++)
    {
        for(int j=0;j<sol[i].size();j++)
        {
            for(int m=0;m<sol.size();m++)
            {
                for(int n=0;n<sol[i].size();n++)
                {
                    if( (sol[i][j] == sol[m][n])  && m>i && j==n)
                    {
                        sol.pop_back();
                        return false;
                    }
                }
            }
        }
    }

    sol.pop_back();
    return true;
}

bool canAdd(int& x,vector<vector<int>>& T,vector<vector<int>>& sol)
{
    // DEVO FARE SOLAMENTE IL canAdd
    if(sol.empty())
        return true;

    if(!check(x,T,sol))
        return false;

    return true;
}

bool bt(vector<vector<int>>& T,vector<vector<int>>& sol,int q)
{
    int x = 0;

    while( x < T.size())
    {
        if(canAdd(x,T,sol))
        {
            add(x,T,sol);

            if(isComplete(sol,q))   return true;
            else if(bt(T,sol,q))    return true;

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
    int Nt,q;

    cin>>Nt>>q;

    string p1,p2;
    int a,b,c;
    vector<int> temp;
    vector<vector<int>> T;

    for(int i=0;i<Nt;i++)
    {
        cin>>p1;
        cin>>a>>b>>c;
        cin>>p2;

        temp.push_back(a);
        temp.push_back(b);
        temp.push_back(c);

        T.push_back(temp);
        temp.clear();
    }

    /* INPUT CON SPAZI PER PRENDERE L'INPUT 

        4 3
        < 42 88 2 >
        < 7 8 1 >
        < 23 8 3 >
        < 23 888 4 >    */

    /*  for(int i=0;i<T.size();i++)
    {
        cout<<"Incantesimo "<<i<<": ";
        for(int j=0;j<T[i].size();j++)
        {
            cout<<T[i][j]<<" ";
        }
        cout<<endl;
    }   */

    vector<vector<int>> sol;

    if(bt(T,sol,q))
    {
        cout<<"SI"<<endl;
        for(int i=0;i<sol.size();i++)
        {
            for(int j=0;j<sol[i].size();j++)
            {
                cout<<sol[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    else    
        cout<<"NO";




    return 0;
}