#include<bits/stdc++.h>
#include "makedata.hpp"
using namespace std;

int n,m,s;
char Name[]="test";

int main()
{
    SetDataName(Name);
    MakeExe();
    MakeMatchExe();

    for(int TEST=1;TEST<=20;++TEST)
    {
        SetDataID(TEST);
        GetIn();

        if(TEST<=6) n=m=10;
        else if(TEST<=14) n=1e4,m=1e4;
        else n=5e5,m=5e5;
        s=RandInt(1,n);

        printf("%d %d %d\n",n,m,s);
        rdTree now=RandTree(n);
        cout<<now;

        for(int i=1;i<=m;++i)
        {
            int a=RandInt(1,n),b=RandInt(1,n);
            printf("%d %d\n",a,b);
        }

        GetOut();
        Match();
    }

    CheckFile(20);
    ClearFile(20);
    return 0;
}