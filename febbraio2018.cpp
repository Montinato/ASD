#include<iostream>
#include<vector>
using namespace std;

//  DEVO COMPLETARLO

bool bt(vector<int>& studenti,vector<vector<int>>& conoscenti,vector<pair<int,int>>& sol,int p)
{

}

int main()
{
    int n,m,p;

    cin>>n>>m>>p;

    vector<int> studenti;
    vector<vector<int>> conoscenti;     // i = studenti ( stessa pos in studenti), j = conoscenti
    int x,y;
    string simbolo;

    studenti.push_back(42); studenti.push_back(8);  studenti.push_back(5);  studenti.push_back(9);

    vector<int> A;  A.push_back(5);
    vector<int> B;  B.push_back(5); B.push_back(9);
    vector<int> C;  C.push_back(42);
    vector<int> D;  D.push_back(42);    D.push_back(8);

    conoscenti.push_back(A);
    conoscenti.push_back(B);
    conoscenti.push_back(C);
    conoscenti.push_back(D);

    /* cout<<"Stampo gli studenti: ";
    for(int i=0;i<studenti.size();i++)
        cout<<studenti[i]<<" ";
    cout<<endl;

    cout<<"Stampo studenti e relativi conoscenti: "<<endl;
    for(int i=0;i<conoscenti.size();i++)
    {
        for(int j=0;j<conoscenti[i].size();j++)
        {
            cout<<conoscenti[i][j]<<" ";
        }
        cout<<endl;
    }       INPUT OK    */

    vector<pair<int,int>> pos;

    pair<int,int> valore;

    for(int i=0;i<conoscenti.size();i++)
    {
        for(int j=0;j<conoscenti[i].size();j++)
        {
            if(possoAssegnare(studenti[0],i,j,conoscenti,sol))
            {
                valore = assegno(studenti[0],conoscenti);
                pos.push_back(valore);
            }
        }
    }




    return 0;
}