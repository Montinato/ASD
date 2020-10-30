#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<list>
using namespace std;

bool inSol(vector<pair<string,int>>& sol,string s)
{
    for(auto i : sol)
        if(i.first == s)
            return true;
    
    return false;
}
// Funzione che mi dice quante directory (nomi) ci sono all'interno di sol
int numeroDirectory(vector<pair<string,int>>& sol)
{
    list<string> nomi;

    for(int i=0;i<sol.size();i++)
    {
        nomi.push_back(sol[i].first);
    }

    nomi.sort();
    nomi.unique();

    for(auto a : nomi)
        cout<<a<<" ";
    cout<<endl;

    return nomi.size();
}

bool check(pair<string,int>& x,vector<pair<string,int>>& sol,int k,int p)
{
    for(int i=0;i<sol.size();i++)
    {
        bool cond = true;

        if((x.first != sol[i].first)&&(numeroDirectory(sol) == k))      // Nome diverso e k directory
            return false;
        else if((x.first != sol[i].first) && (numeroDirectory(sol) < k))  // Nome diverso ma meno di k directory
        {
            for(auto a : sol)
                if(a.second == x.second)
                    cond = false;

            if(cond)
                return true;
        }
        else if((x.first == sol[i].first) && (numeroDirectory(sol) <= k))  // Stesso nome, se hanno un numero diverso posso aggiungere 
        {
            for(auto b : sol)
                if(b.second == x.second )
                    cond = false;

            if(cond)
                return true;
        }
        else if((x.first == sol[i].first) && (numeroDirectory(sol) == k)) // Stesso nome, numero delle directory = k, se e' un numero che non e' inserito posso aggiungere
        {
            for(auto c : sol)
                if(c.second == x.second)
                    cond = false;

            if(cond)
                return true;
        }

        cond = true;
    }

    return false;
}

int main()
{

    string s;
    int x;
    vector<pair<string,int>> V;

    pair<string,int> a("ab",4);
    pair<string,int> b("ab",8);
    pair<string,int> c("ab",12);
    pair<string,int> d("ab",8);

    pair<string,int> aa("xyz",7);
    pair<string,int> bb("xyz",4);
    pair<string,int> cc("xyz",7);
    pair<string,int> dd("xyz",4);
    pair<string,int> ee("xyz",12);
    pair<string,int> ff("xyz",4);

    pair<string,int> aaa("q",320);
    pair<string,int> bbb("q",11);
    pair<string,int> ccc("q",7);


    V.push_back(a);
    V.push_back(b);
    V.push_back(c);
    V.push_back(d);
    V.push_back(aa);
    V.push_back(bb);
    V.push_back(cc);
    V.push_back(dd);
    V.push_back(ee);
    V.push_back(ff);
    V.push_back(aaa);
    V.push_back(bbb);
    V.push_back(ccc);


   // cout<<numeroDirectory(V);


    int k=2,p=6;
    vector<pair<string,int>> sol;

    pair<string,int> kk("kk",14);

    sol.push_back(kk);

    pair<string,int> xd("aa",13);

    if(check(xd,sol,k,p))
        cout<<"PORCODIO";
    else    
        cout<<"NO";

   
}