/*
    Dati in input P, p1 e p2, si deve restituire il numero minimo di mosse valide che si devono effettuare per
    trasformare p1 in p2. Se non si può trasformare la parola p1 in p2, allora si deve restituire-1.
    Tutte le parole in P hanno la stessa lunghezza.
*/

#include<iostream>
#include<string>
#include<vector>
using namespace std;

bool completamenteDiverse(string& A,string& B)
{
    int cont = 0;

    for(int i=0;i<A.size();i++)
    {
        for(int j=0;j<B.size();j++)
        {
            if(A[i] == B[j])
                cont++;
        }
    }

    if(cont == 0)
        return true;

    return false;
    
}

bool check(const vector<string>& parole,string& A,string& B,int& num)
{
    if(completamenteDiverse(A,B))
        return false;

    string C;
    bool ok = false;
    vector<char> temp,occ;
    vector<int> pos,pos1;
    int sol = 100;

    for(int i=0;i<A.size();i++)
    {
        for(int j=0;j<B.size();j++)
        {
            if(A[i] == B[j])
                ok = true;
        }

        if(!ok)
        {
            temp.push_back(B[i]);
            pos.push_back(i);       // So in che posizione devo sostituire/inserire le lettere
        }
        else
        {
            occ.push_back(A[i]);       // Occorrenze uguali delle parole
            pos1.push_back(i);         // Posizione delle lettere
        }
        
        ok = false;
    }       // Fino a qui so le lettere diverse tra le due parole 


    // Cerco le parole con le lettere in comune e provo a sostituire
    string n = A;
    bool cond = false;

   // cout<<"Prima n: "<<n<<endl;
    int conta = 0;
        
    for(int j=0;j<pos.size() && conta < temp.size() ;j++)
    {
        n[pos[j]] = temp[conta++];

        for(int i=0;i<parole.size();i++)
        {
            if(n == parole[i])
                cond = true;
        }
           
        if(!cond)
            break;
        else 
            num++;


        if(num < sol)
            sol = num;

        cond = false;
           
      // cout<<"Seconda n: "<<n<<endl;
    }
    
    if(num == A.size())
        return false;

    return true;
}

int main()
{
    int P,presente=0;
    string P1,P2,x;
    vector<string> parole;

    cin>>P>>P1>>P2;

    for(int i=0;i<P;i++)
    {
        cin>>x;
        parole.push_back(x);
    }

    for(int i=0;i<parole.size();i++)
    {
        if(P1 == parole[i])
            presente++;
        
        if(P2 == parole[i])
            presente++;
    }

    int n = 0;

    if(presente == 2)
    {
        if(check(parole,P1,P2,n))
            cout<<n<<endl;
        else    
            cout<<"-1"<<endl;
    }


    return 0;
}
