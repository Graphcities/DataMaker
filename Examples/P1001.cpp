#include<bits/stdc++.h>
#include "makedata.hpp"
using namespace std;

char Name[]="test";

int main()
{
    SetDataName(Name);
    MakeExe();

    for(int i=1;i<=20;++i)
    {
        SetDataID(i);
        GetIn();
        int x=RandInt(),y=RandInt();
        printf("%d %d\n",x,y);
        GetOut();
    }
    return 0;
}