#include<iostream>
#include<string>
#include<vector>
using namespace std;

int profondita(vector<pair<int,int>>& sol)
{
    if(sol.empty())
        return 1;

    int conto = -1;
    int figlio = 0;

    for(int i=0;i<sol.size();i++)
    {
        for(int j=0;j<sol.size();j++)
        {
            if(sol[i].first == sol[j].first)
                figlio++;
        }

        if( (figlio == 1) || (figlio ==2) )
            conto++;

        figlio = 0;
    }

    return conto;

}

int main()
{
    int n;
    int radice=0,nuova,vecchia,tappo;
    char dir,simbolo;
    int p;

    vector<pair<int,int>> V;
    pair<int,int> coppia;
    int min = 100, max = -100;


    cin >> n;

    int cont = n;

    /*  INSERIMENTO PRIMO TEST CASE 
    for(int k=0;k<n;k++)
    {
        cin >> radice;
        
        for(int i=0;i<cont;i++)
        {
            cin>>nuova>>simbolo>>vecchia>>dir;

            coppia.first = vecchia;
            coppia.second = nuova;

            V.push_back(coppia);
        
        }

        p = profondita(V);
        cont--;

        if( p > max)
            max = p;
        
        if( p < min)
            min = p;
        cin >> tappo;

    }   */

    coppia.first = 0;
    coppia.second = 3;
    V.push_back(coppia);

    coppia.first = 0;
    coppia.second = 2;
    V.push_back(coppia);

    
    coppia.first = 2;
    coppia.second = 4;
    V.push_back(coppia);

    coppia.first = 2;
    coppia.second = 1;
    V.push_back(coppia);

    coppia.first = 1;
    coppia.second = 5;
    V.push_back(coppia);
    
    
    p = profondita(V);
        

    if( p > max)
        max = p;

    min = 1;

    cout<<"("<<min<<","<<max<<")";

    return 0;
}
