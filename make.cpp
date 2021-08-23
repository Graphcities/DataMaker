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

        // Do something...

        GetOut();
    }
    return 0;
}