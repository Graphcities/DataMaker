#include<bits/stdc++.h>
#include "makedata.hpp"
using namespace std;

int n,m;
char Name[]="test";

int main()
{
    SetDataName(Name);
    MakeExe();

    for(int TEST=1;TEST<=20;++TEST)
    {
        SetDataID(TEST);
        GetIn();

        if(TEST<=6) n=8,m=10;
        else if(TEST<=14) n=1e3,m=1e4;
        else n=1e5,m=1e5;

        printf("%d %d\n",n,m);
        rdArray arr=RandArray(n,-1e6,1e6);
        cout<<arr;

        for(int i=1;i<=m;++i)
        {
            int typ=RandInt(1,2),l=RandInt(1,n),r=RandInt(1,n);
            if(l>r) swap(l,r);
            if(typ==1)
            {
                int k=RandInt(-1e6,1e6);
                printf("%d %d %d %d\n",typ,l,r,k);
            }
            else printf("%d %d %d\n",typ,l,r);
        }

        GetOut();
    }
    return 0;
}