#include<bits/stdc++.h>
typedef long long ll;
const int Maxlen=2e6+5;

// Random!
std::mt19937_64 engine(std::chrono::steady_clock::now().time_since_epoch().count());
ll RandInt(ll l=1,ll r=1ll*1e9)
{
    assert(l<=r);
    std::uniform_int_distribution<ll> dist(l,r);
    return dist(engine);
}
double Randec(double l=1,double r=1e9,int digit=2)
{
    assert(l<=r && digit>=0);
    ll mult=pow(10,digit),rdl=l*mult,rdr=r*mult;
    return 1.0*RandInt(rdl,rdr)/mult;
}

// Random Array!
struct rdArray
{
    int n,typ; ll rdMin,rdMax; bool isDiff;
    // 长度 种类 最小值 最大值 是否互不相同
    // 1数列, 2排列, 3字符串
    ll rdlist[Maxlen];
    rdArray(): n(0),typ(0),rdMin(1ll),rdMax(1ll*1e9),isDiff(false),rdlist() {}
    ll& operator()(int x) {assert(x<=n); return rdlist[x];}
    void Shuffle() // 洗牌
    {
        for(int i=n;i>=1;--i)
            std::swap(rdlist[i],rdlist[RandInt(1,i)]);
    }
    void Insert(int p,ll k) // 插入
    {
        n++;
        assert(p>=1 && p<=n);
        for(int i=n;i>p;--i) rdlist[i]=rdlist[i-1];
        rdlist[p]=k;
    }
    void Delete(int p) // 删除
    {
        assert(n>=1 && p>=1 && p<=n);
        n--;
        for(int i=p;i<=n;++i) rdlist[i]=rdlist[i+1];
    }
};
std::ostream &operator<<(std::ostream &out,const rdArray &now) // 重定义输出流
{
    for(int i=1;i<=now.n;++i) out<<now.rdlist[i]<<' ';
    out<<std::endl;
    return out;
}
std::map<ll,bool> rdArraymp;
rdArray RandArray(int n,ll rdMin=1,ll rdMax=1ll*1e9,bool isDiff=false) // 构造数列
{
    assert(n>=0 && rdMin<=rdMax);
    rdArray now;
    now.n=n,now.typ=1,now.rdMin=rdMin,now.rdMax=rdMax,now.isDiff=isDiff;
    if(!isDiff) for(int i=1;i<=n;++i) now.rdlist[i]=RandInt(rdMin,rdMax);
    else
    {
        assert(rdMax-rdMin+1>=n);
        rdArraymp.clear();
        for(int i=1;i<=n;++i)
        {
            int res=RandInt(rdMin,rdMax);
            while(rdArraymp[res]==true) res=RandInt(rdMin,rdMax);
            now.rdlist[i]=res; rdArraymp[res]=true;
        }
    }
    return now;
}
rdArray RandRange(int n) // 构造排列
{
    assert(n>=0);
    rdArray now;
    now.n=n,now.typ=2,now.rdMin=1,now.rdMax=n,now.isDiff=true;
    for(int i=1;i<=n;++i) now.rdlist[i]=i;
    now.Shuffle();
    return now;
}

// RandString!
struct rdString:rdArray
{
    int rdsiz; // 字符集大小
    char rdletter[50]; // 字符集
};
std::ostream &operator<<(std::ostream &out,const rdString &now) // 重定义输出流
{
    for(int i=1;i<=now.n;++i) out<<now.rdletter[now.rdlist[i]];
    out<<std::endl;
    return out;
}
rdString RandString(int n,ll rdMin=0,ll rdMax=25) // 构造字符串
{
    rdString now;
    assert(n>=0 && rdMin<=rdMax && rdMin>=0 && rdMax<=25);
    now.n=n,now.typ=3,now.rdMin=rdMin,now.rdMax=rdMax,now.isDiff=false;
    now.rdsiz=rdMax-rdMin+1;
    for(int i=0;i<now.rdsiz;++i) now.rdletter[i]=rdMin+i+'a';
    for(int i=1;i<=n;++i) now.rdlist[i]=RandInt(0,now.rdsiz-1);
    return now;
}
rdString RandSpeStr(int n,int rdsiz,char rdletter[]) // 构造特殊字符集字符串
{
    rdString now;
    assert(n>=0 && rdsiz>=0 && rdsiz<50);
    now.n=n,now.typ=3,now.rdMin=0,now.rdMax=rdsiz-1,now.isDiff=false;
    now.rdsiz=rdsiz;
    for(int i=0;i<rdsiz;++i) now.rdletter[i]=rdletter[i];
    for(int i=1;i<=n;++i) now.rdlist[i]=RandInt(0,rdsiz-1);
    return now;
}

// Stream!
int DataID;
char dataname[30],filename[30],inname[]=".in",outname[]=".out",filepos[]="Data\\";
void SetDataName(char dname[]) {strcpy(dataname,dname);} // 设置文件名
void SetDataID(int dID) {assert(dID>=1); DataID=dID;} // 设置当前数据编号
void MakeExe() {system("g++ Program\\std.cpp -o Program\\std --std=c++11 -O2");} // 生成.exe文件
void GetIn() // 设置输入
{
    strcpy(filename,filepos); strcat(filename,dataname);
    char fileid[5]; sprintf(fileid,"%d",DataID);
    strcat(filename,fileid); strcat(filename,inname);
    freopen("CON","r",stdin);
	freopen("CON","w",stdout);
	freopen(filename,"w",stdout);
}
void GetOut() // 设置输出
{
    freopen("CON","r",stdin);
	freopen("CON","w",stdout);
    printf("Successfully GetIn  TestData %d !\n",DataID);

    strcpy(filename,filepos); strcat(filename,dataname);
    char fileid[5]; sprintf(fileid,"%d",DataID);
    strcat(filename,fileid); strcat(filename,inname);
    freopen(filename,"r",stdin);

    strcpy(filename,filepos); strcat(filename,dataname);
    strcat(filename,fileid); strcat(filename,outname);
    freopen(filename,"w",stdout);

    system("Program\\std.exe");

    freopen("CON","r",stdin);
	freopen("CON","w",stdout);
    printf("Successfully GetOut TestData %d !\n",DataID);
}