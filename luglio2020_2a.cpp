#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

void add(int x,vector<vector<string>>& S,vector<vector<string>>& sol)
{
    sol.push_back(S[x]);
}

void remove(vector<vector<string>>& sol)
{
    sol.pop_back();
}

bool canAdd(int x,vector<vector<string>>& S,vector<vector<string>>& sol)
{
    if(sol.empty())
        return true;

    for(int i=0;i<sol.size();i++)
    {
        if(sol[i] == S[x])
            return false;
    }

    return true;
}

bool condition(vector<string>& U,vector<vector<string>>& sol)
{
    vector<int> temp = U;
    vector<string> V;

    for(int i=0;i<sol.size();i++)
    {
        for(int j=0;j<sol[i].size();j++)
        {
            for(int k=0;k<U.size();k++)
            {
                if(U[k] == sol[i][j])
                    V.push_back(U[k]);
            }
        }
    }

    sort(temp.begin(),temp.end());
    sort(V.begin(),V.end());

    return U == V;

}

bool isComplete(vector<string>& U,vector<vector<string>>& sol,int& k)
{
    if(!condition(U,sol))
        return false;

    return sol.size() == k;
}

bool bt(vector<string>& U,vector<vector<string>>& S,int k,vector<vector<string>>& sol)
{
    int x = 0;

    while( x < S.size())
    {
        if(canAdd(x,S,sol))
        {
            add(x,S,sol);

            if(isComplete(U,sol,k)) return true;
            else if(bt(U,S,k,sol))  return true;

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
    vector<string> U;

    string a ="a";     string b = "b";   string c = "xq";  string d = "e";   string e = "f";

    U.push_back(a);     U.push_back(b);   U.push_back(c);    U.push_back(d);   U.push_back(e); 

    vector<vector<string>> S;

    vector<string> A;  A.push_back("xq");  A.push_back("e");   A.push_back("f");
    S.push_back(A);

    A.clear();
    A.push_back("b");   A.push_back("e");   A.push_back("f");
    S.push_back(A);

    A.clear();
    A.push_back("a");   A.push_back("b");
    S.push_back(A);

    A.clear();
    A.push_back("xq");  A.push_back("f"); 
    S.push_back(A);

    A.clear();
    A.push_back("a");   A.push_back("xq");     A.push_back("e");
    S.push_back(A);

    int k = 3;

    /*
    cout<<"Stampa di U: "<<endl;
    for(int i=0;i<U.size();i++)
        cout<<U[i]<<" ";
    cout<<endl;

    cout<<"Stampa di S: "<<endl;
    for(int i=0;i<S.size();i++)
    {
        for(int j=0;j<S[i].size();j++)
            cout<<S[i][j]<<" ";
        cout<<endl;
    }              

    cout<<"Stampa di k: "<<k<<endl;     */      


    vector<vector<string>> sol;


    if(bt(U,S,k,sol))
    {
        cout<<"SI";
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