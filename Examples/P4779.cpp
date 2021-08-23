#include<bits/stdc++.h>
#include "makedata.hpp"
using namespace std;

int n,m,s;
char Name[]="test";

int main()
{
    SetDataName(Name);
    MakeExe();

    for(int TEST=1;TEST<=20;++TEST)
    {
        SetDataID(TEST);
        GetIn();

        n=int(1e5),m=int(2e5),s=1;
        printf("%d %d %d\n",n,m,s);
        if(TEST&1)
        {
            rdGraph now=RandGraph(n,m,true,true,false,1ll,1e4);
            cout<<now;
        }
        else
        {
            rdGraph now=RandHackSPFA(n,m,true,1ll,1e4);
            cout<<now;
        }

        GetOut();
    }
    return 0;
}