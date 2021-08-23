#include<bits/stdc++.h>
#include "makedata.hpp"
using namespace std;
const int Maxn=5e5;

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

        if(TEST<=2) n=m=991;
        else if(TEST<=4) n=m=992;
        else if(TEST<=5) n=m=993;
        else if(TEST<=8) n=m=99994;
        else if(TEST<=12) n=m=99995;
        else if(TEST<=16) n=m=99996;
        else if(TEST<=19) n=m=99997;
        else n=m=299998;
        printf("%d %d\n",n,m);

        if(TEST>=6 && TEST<=8)
        {
            rdTree now=RandChain(n);
            cout<<now;
        }
        else
        {
            rdTree now=RandTree(n);
            cout<<now;
        }

        if(TEST>=3 && TEST<=4)
        {
            rdArray w=RandArray(n,0,0);
            cout<<w;
        }
        else
        {
            rdArray w=RandArray(n,0,n);
            cout<<w;
        }

        if(TEST>=1 && TEST<=2)
        {
            rdArray s=RandArray(n,1,n);
            for(int i=1;i<=n;++i) printf("%lld %lld\n",s(i),s(i));
        }
        else if(TEST>=9 && TEST<=12)
        {
            rdArray s=RandArray(n,1,1);
            rdArray t=RandArray(n,1,n);
            for(int i=1;i<=n;++i) printf("%lld %lld\n",s(i),t(i));
        }
        else if(TEST>=13 && TEST<=16)
        {
            rdArray s=RandArray(n,1,n);
            rdArray t=RandArray(n,1,1);
            for(int i=1;i<=n;++i) printf("%lld %lld\n",s(i),t(i));
        }
        else
        {
            rdArray s=RandArray(n,1,n);
            rdArray t=RandArray(n,1,n);
            for(int i=1;i<=n;++i) printf("%lld %lld\n",s(i),t(i));
        }

        GetOut();
    }
    return 0;
}