#include<iostream>
#include<vector>
#include<string>
#include<list>
using namespace std;

bool in(vector<pair<string,int>>& sol,pair<string,int> x)
{
    for(auto a : sol)
        if(a.first == x.first)
            return true;

    return false;
}

void add(int x,vector<pair<string,int>>& V,vector<pair<string,int>>& sol)
{
    //cout<<"Metodo add: aggiungo "<<V[x].first<<" "<<V[x].second<<endl;
    sol.push_back(V[x]);
}

void remove(vector<pair<string,int>>& V)
{
    vector<pair<string,int>>::iterator it = V.end()-1;
    pair<string,int> val((*it).first,(*it).second);

   // cout<<"Metodo remove: rimuovo "<<val.first<<" "<<val.second<<endl;
    V.pop_back();
}

int numeroDirectory(vector<pair<string,int>>& sol)
{
    list<string> nomi;

    for(int i=0;i<sol.size();i++)
    {
        nomi.push_back(sol[i].first);
    }

    nomi.sort();
    nomi.unique();

   /* for(auto a : nomi)
        cout<<a<<" ";
    cout<<endl; */

    return nomi.size();
}


bool check(pair<string,int>& x,vector<pair<string,int>>& sol,int k,int p)
{
    //cout<<"Metodo check: "<<endl;
    bool cond = false;

    for(int i=0;i<sol.size();i++)
    {
        if(sol[i].first == x.first)
        {
          //  cout<<sol[i].first<<" fa parte della sol, quindi posso aggiungere "<<x.first<<" "<<x.second<<endl;
            cond = true;
            break;
        }

        if(!cond)
        {
           if((numeroDirectory(sol)==k)&&(!in(sol,x)))
           {
               // cout<<"Il numero di directory presenti e' gia' "<<k<<" non posso aggiungere"<<endl;
                return false;
           }
        }
    }

    return true;
}

bool canAdd(int x,vector<pair<string,int>>& V,vector<pair<string,int>>& sol,int k,int p)
{
  // cout<<"Metodo canAdd: "<<endl;
    if(sol.empty()) 
    {
        //cout<<"La sol e' vuota, aggiungo: "<<V[x].first<<" "<<V[x].second<<endl;
        return true;
    }   
    bool condition = true;

    for(int j=0;j<sol.size();j++)           
    {
        if(V[x] == sol[j])                  // Non posso inserire lo stessso valore
        {   
          // cout<<"V[x] vale : "<<V[x].first<<" "<<V[x].second<<endl<<"Sol[j] vale: "<<sol[j].first<<" "<<sol[j].second<<endl<<"NON POSSO AGGIUNGERE "<<endl; 
            condition = false; 
            break;
        }
        else if((V[x].second == sol[j].second))
        {
           // cout<<"Il numero "<<V[x].second<<" e' gia' presente NON POSSO AGGIUNGERE "<<endl;
            condition = false;
            break;
        }
    }

    if(condition)
    {
      // cout<<V[x].first<<" "<<V[x].second<<" non e' presente in sol "<<",se arrivo qui vado dentro il metodo check "<<endl;
        if(check(V[x],sol,k,p))             // Se confronti dei valori diversi entro in check
            return true;
    }

    return false;
}

bool isComplete(vector<pair<string,int>>& V,vector<pair<string,int>>& sol,int k,int p)
{
   //cout<<"La soluzione e' completa quando il num di directory e' k=2 e le persone presenti in sol sono >=i di p"<<endl;
    return numeroDirectory(sol) <= k && sol.size()>=p; 
}

bool bt(vector<pair<string,int>>& V,vector<pair<string,int>>& sol,int k,int p)
{
    int x = 0;

    while( x < V.size())
    {
     //  cout<<"Metodo bt: "<<endl;
        if(canAdd(x,V,sol,k,p)) 
        {
            add(x,V,sol);

            if(isComplete(V,sol,k,p))   return true;
            else if(bt(V,sol,k,p))  return true;

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
    int n,k,p;

    cin>>n>>k>>p;

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


    vector<pair<string,int>> sol;

  /*  for(int i=0;i<V.size();i++)
        cout<<V[i].first<<" "<<V[i].second<<endl;   */

    cout<<endl;

    if(bt(V,sol,k,p))
    {
        cout<<"SI"<<endl;
        for(int i=0;i<sol.size();i++)
            cout<<sol[i].first<<" "<<sol[i].second<<endl;
    }
    else    
    {
        cout<<"NO";
        for(int i=0;i<sol.size();i++)
            cout<<sol[i].first<<" "<<sol[i].second<<endl;
    }


    return 0;
}