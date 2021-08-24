#include<bits/stdc++.h>
typedef long long ll;
typedef std::pair<int,int> Pair;

// Const!
const int Maxlen=2e6+5;
const double PI=acos(-1);
const double E=exp(1);
char ALPHABET_SMALL[]="abcdefghijklmnopqrstuvwxyz";
char ALPHABET_CAPITAL[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char ALPHABET[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char NUMBERS[]="0123456789";
char ZEROANDONE[]="01";

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
    char rdletter[100]; // 字符集
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
rdString RandBrac(int n) // 构造随机括号序列
{
    rdString now;
    assert(n%2==0 && n>=0);
    n>>=1;
    const int len=n<<1;
    bool arr[len];
    std::fill(arr,arr+n,1);
    std::fill(arr+n,arr+len,0);
    std::shuffle(arr,arr+len,engine);
    int start=0,end=len;
    while(1)
    {
        int lef_count=0,rig_count=0;
        bool ok=true;
        for(int i=start,j;i<end;++i)
        {
            ++(arr[i]?rig_count:lef_count);
            if(lef_count>=rig_count) continue;
            for(j=i+1;j<end;++j)
            {
                ++(arr[j]?rig_count:lef_count);
                if (rig_count>lef_count) continue;
                const int len=j-i-1;
                std::rotate(arr+i+1,arr+j+1,arr+end);
                std::copy_backward(arr+end-len-1,arr+end-1,arr+end);
                std::transform(arr+end-len,arr+end,arr+end-len,std::logical_not<bool>());
                arr[i]=0; arr[end-len-1]=1;
                start=i+1; end=end-len-1;
                ok=false;
                break;
            }
        }
        if(ok)break;
    }
    now.n=len,now.rdMin=0,now.rdMax=1,now.isDiff=false;
    now.rdsiz=2,now.rdletter[0]='(',now.rdletter[1]=')';
    for(int i=0;i<len;++i) now.rdlist[i+1]=arr[i];
    return now;
}

// Stream!
int DataID;
char dataname[30],filename[30],inname[]=".in",outname[]=".out";
char filepos[]="Data\\",matchname[]="match",matchpos[]="Program\\";
void SetDataName(char dname[]) {strcpy(dataname,dname);} // 设置文件名
void SetDataID(int dID) {assert(dID>=1); DataID=dID;} // 设置当前数据编号
void MakeExe() {system("g++ Program\\std.cpp -o Program\\std --std=c++11 -O2");} // 生成.exe文件
void MakeMatchExe() {system("g++ Program\\match.cpp -o Program\\match --std=c++11 -O2");} // 生成对拍.exe
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
void Match() // 生成对拍文件
{
    strcpy(filename,filepos); strcat(filename,dataname);
    char fileid[5]; sprintf(fileid,"%d",DataID);
    strcat(filename,fileid); strcat(filename,inname);
    freopen(filename,"r",stdin);

    strcpy(filename,filepos); strcat(filename,dataname);
    strcat(filename,fileid); strcat(filename,outname);
    char prename[30]; strcpy(prename,filename);

    strcpy(filename,matchpos); strcat(filename,matchname);
    strcat(filename,fileid); strcat(filename,outname);
    freopen(filename,"w",stdout);

    system("Program\\match.exe");

    freopen("CON","r",stdin);
	freopen("CON","w",stdout);
    printf("Successfully Match  TestData %d !\n",DataID);
}
void CheckFile(int AllID) // 开始对拍
{
    freopen("Program\\result.txt","w",stdout);

    for(int i=1;i<=AllID;++i)
    {
        char fileid[5]; sprintf(fileid,"%d",i);
        strcpy(filename,filepos); strcat(filename,dataname);
        strcat(filename,fileid); strcat(filename,outname);
        char prename[30]; strcpy(prename,filename);
        strcpy(filename,matchpos); strcat(filename,matchname);
        strcat(filename,fileid); strcat(filename,outname);

        char fcname[70]="fc /W ";
        strcat(fcname,prename); strcat(fcname," "); strcat(fcname,filename);
        system(fcname);
    }

    freopen("CON","r",stdin);
	freopen("CON","w",stdout);
    printf("\nSuccessfully Check %d Files !",AllID);
}
void ClearFile(int AllID) // 清除对拍文件
{
    freopen("Program\\result.txt","a",stdout);

    for(int i=1;i<=AllID;++i)
    {
        char delname[30];
        sprintf(delname,"del Program\\match%d.out",i);
        system(delname);
    }

    freopen("CON","r",stdin);
	freopen("CON","w",stdout);
    printf("\nSuccessfully Clear %d Files !",AllID);
}

// Random Graph!
struct Link{int frm,to,nxt; ll w;}; // 边
struct rdGraph
{
    int n,m,tot,Head[Maxlen],fa[Maxlen];
    ll rdMin,rdMax; bool isDir,isCon,isRep,isVal;
    // 点数 边数 计数器 Head 并查集 边权范围 是否有向 是否连通 是否重边自环 是否有边权
    Link Edge[Maxlen*2];
    rdGraph(): n(0),m(0),tot(0),rdMin(1),rdMax(1),isDir(false),isCon(false),isRep(false),isVal(false) {}
    int Find(int x) {return x==fa[x]?x:fa[x]=Find(fa[x]);} // 找祖先
    void Addedge(int x,int y,ll z) // 加边
    {
        Edge[++tot]=(Link){x,y,Head[x],z};
        Head[x]=tot,fa[Find(x)]=Find(y);
    }
    bool isConnect(int x,int y) {return (Find(x)==Find(y));} // 是否连通
};
std::ostream &operator<<(std::ostream &out,const rdGraph &now) // 重定义输出流
{
    int st[now.tot];
    for(int i=0;i<now.tot;++i) st[i]=i+1;
    std::shuffle(st,st+now.tot,engine);
    for(int i=0;i<now.tot;++i)
    {
        int x=now.Edge[st[i]].frm,y=now.Edge[st[i]].to; ll z=now.Edge[st[i]].w;
        if(!now.isVal) out<<x<<' '<<y<<std::endl;
        else out<<x<<' '<<y<<' '<<z<<std::endl;
    }
    return out;
}
std::map<Pair,bool> rdGraphmp;
rdGraph RandGraph(int n,int m,bool isDir=false,bool isCon=false,
                  bool isRep=false,ll rdMin=1,ll rdMax=1) // 随机建图
{
    rdGraph now;
    assert(n>=1 && m>=0 && rdMin<=rdMax);
    for(int i=1;i<=n;++i) now.fa[i]=i;
    now.n=n,now.m=m,now.rdMin=rdMin,now.rdMax=rdMax;
    now.isDir=isDir,now.isCon=isCon,now.isRep=isRep; rdGraphmp.clear();
    now.isVal=(rdMin!=1ll || rdMax!=1ll);
    if(!isRep)
    {
        if(!isDir) assert(1ll*m<=1ll*n*(n-1)/2ll);
        else assert(1ll*m<=1ll*n*(n-1));
    }
    if(!isCon)
    {
        for(int i=1;i<=m;++i)
        {
            int a=RandInt(1,n),b=RandInt(1,n),c=RandInt(rdMin,rdMax);
            if(!isRep) while(a==b || rdGraphmp[std::make_pair(a,b)]==true) a=RandInt(1,n),b=RandInt(1,n);
            now.Addedge(a,b,c);
            if(!isDir) rdGraphmp[std::make_pair(a,b)]=true,rdGraphmp[std::make_pair(b,a)]=true;
            else rdGraphmp[std::make_pair(a,b)]=true;
        }
    }
    else
    {
        assert(m>=n-1);
        int deg[n+1],prufer[n-2]; // prufer 序列随机生成树
        for(int i=0;i<n-2;++i) prufer[i]=RandInt(1,n);
        std::fill(deg+1,deg+n+1,1);
        for(int i=0;i<n-2;++i) ++deg[prufer[i]];
        int ptr=0; while(deg[++ptr]!=1);
        int leaf=ptr;
        for(int i=0;i<n-2;++i)
        {
            int x=prufer[i];
            now.Addedge(x,leaf,RandInt(rdMin,rdMax)),rdGraphmp[std::make_pair(x,leaf)]=true;
            if(!isDir) rdGraphmp[std::make_pair(leaf,x)]=true;
            if(--deg[x]==1 && x<ptr) leaf=x;
            else
            {
                while(deg[++ptr]!=1);
                leaf=ptr;
            }
        }
        now.Addedge(leaf,n,RandInt(rdMin,rdMax)),rdGraphmp[std::make_pair(leaf,n)]=true;
        if(!isDir) rdGraphmp[std::make_pair(n,leaf)]=true;

        for(int i=1;i<=m-n+1;++i)
        {
            int a=RandInt(1,n),b=RandInt(1,n),c=RandInt(rdMin,rdMax);
            if(!isRep) while(a==b || rdGraphmp[std::make_pair(a,b)]==true) a=RandInt(1,n),b=RandInt(1,n);
            now.Addedge(a,b,c);
            if(!isDir) rdGraphmp[std::make_pair(a,b)]=true,rdGraphmp[std::make_pair(b,a)]=true;
            else rdGraphmp[std::make_pair(a,b)]=true;
        }
    }
    return now;
}
rdGraph RandHackSPFA(int n,int m,bool isDir=false,ll rdMin=1,ll rdMax=1) // 构造卡SPFA图
{
    assert(n>=1 && m>=0 && rdMin<=rdMax);
    rdGraph now; rdGraphmp.clear();
    now.n=n,now.m=m,now.isDir=isDir,now.isCon=false,now.isRep=false,now.isVal=true;
    int res=0;
    for(int i=n;i>=2;--i)
    {
        now.Addedge(1,i,(n-i+1)*2+1),rdGraphmp[std::make_pair(i,(n-i+1)*2+1)]=true;
        if(!isDir) rdGraphmp[std::make_pair((n-i+1)*2+1,i)]=true;
        now.Addedge(i,i-1,1),res+=2,rdGraphmp[std::make_pair(i,i-1)]=true;
        if(!isDir) rdGraphmp[std::make_pair(i-1,i)]=true;
    }
    for(int i=1;i<=m-res;++i)
    {
        int a=RandInt(1,n),b=RandInt(1,n),c=RandInt(rdMin,rdMax);
        while(a==b || rdGraphmp[std::make_pair(a,b)]==true) a=RandInt(1,n),b=RandInt(1,n);
        now.Addedge(a,b,c);
        if(!isDir) rdGraphmp[std::make_pair(a,b)]=true,rdGraphmp[std::make_pair(b,a)]=true;
        else rdGraphmp[std::make_pair(a,b)]=true;
    }
    return now;
}
rdGraph RandDAG(int n,int m,ll rdMin=1,ll rdMax=1) // 构造随机DAG
{
    rdGraph now;
    rdArray res=RandRange(n); rdGraphmp.clear();
    assert(n>=1 && m>=0 && rdMin<=rdMax && 1ll*m<=1ll*n*(n+1)/2ll);
    now.n=n,now.m=m,now.isRep=false,now.isCon=false,now.isDir=false;
    now.isVal=(rdMin!=1ll || rdMax!=1ll);
    for(int i=1;i<=m;++i)
    {
        int a=RandInt(1,n),b=RandInt(1,n);
        if(a>b) std::swap(a,b);
        while(a==b || rdGraphmp[std::make_pair(a,b)]==true)
        {
            a=RandInt(1,n),b=RandInt(1,n);
            if(a>b) std::swap(a,b);
        }
        rdGraphmp[std::make_pair(a,b)]=true;
        now.Addedge(res(a),res(b),RandInt(rdMin,rdMax));
    }
    return now;
}

// Random Tree!
struct rdTree:rdGraph
{
    int typ; // 种类
    // 1树, 2链, 3菊花图, 4二叉树
};
rdTree RandTree(int n,ll rdMin=1,ll rdMax=1) // prufer 序列随机构造树
{
    assert(n>=1 && rdMin<=rdMax);
    rdTree now;
    now.n=n,now.m=n-1,now.isDir=false,now.isCon=true,now.isRep=false,now.typ=1;
    now.isVal=(rdMin!=1ll || rdMax!=1ll);
    int deg[n+1],prufer[n-2];
    for(int i=0;i<n-2;++i) prufer[i]=RandInt(1,n);
    std::fill(deg+1,deg+n+1,1);
    for(int i=0;i<n-2;++i) ++deg[prufer[i]];
    int ptr=0; while(deg[++ptr]!=1);
    int leaf=ptr;
    for(int i=0;i<n-2;++i)
    {
        int x=prufer[i];
        if(RandInt(1,2)==1) now.Addedge(x,leaf,RandInt(rdMin,rdMax));
        else now.Addedge(leaf,x,RandInt(rdMin,rdMax));
        if(--deg[x]==1 && x<ptr) leaf=x;
        else
        {
            while(deg[++ptr]!=1);
            leaf=ptr;
        }
    }
    if(RandInt(1,2)==1) now.Addedge(leaf,n,RandInt(rdMin,rdMax));
    else now.Addedge(n,leaf,RandInt(rdMin,rdMax));
    return now;
}
rdTree RandBranch(int n,int branch=int(1e9),ll rdMin=1,ll rdMax=1) // 构造随机k叉树
{
    assert(n>=1 && rdMin<=rdMax && branch>=1 && branch<=n);
    rdTree now;
    now.n=n,now.m=n-1,now.isDir=false,now.isCon=true,now.isRep=false,now.typ=1;
    int res[n+1],ind[n+1];
    for(int i=1;i<=n;++i) res[i]=i,ind[i]=0;
    std::shuffle(res+1,res+n+1,engine);
    for(int i=2;i<=n;++i)
    {
        int a=RandInt(1,i-1);
        while(ind[a]>=branch) a=RandInt(1,i-1);
        now.Addedge(res[a],res[i],RandInt(rdMin,rdMax));
        ind[a]++;
    }
    return now;
}
rdTree RandChain(int n,bool isSorted=true,ll rdMin=1,ll rdMax=1) // 构造随机链
{
    assert(n>=1 && rdMin<=rdMax);
    rdTree now;
    int res[n+1];
    for(int i=1;i<=n;++i) res[i]=i;
    if(!isSorted) std::shuffle(res+1,res+n+1,engine);
    now.n=n,now.m=n-1,now.isDir=false,now.isCon=true,now.isRep=false,now.typ=2;
    now.isVal=(rdMin!=1ll || rdMax!=1ll);
    for(int i=1;i<n;++i) now.Addedge(res[i],res[i+1],RandInt(rdMin,rdMax));
    return now;
}
rdTree RandFlower(int n,int root=1,ll rdMin=1,ll rdMax=1) // 构造随机菊花图
{
    assert(n>=1 && rdMin<=rdMax);
    rdTree now;
    int res[n+1];
    for(int i=1;i<=n;++i) res[i]=i;
    std::shuffle(res+1,res+n+1,engine);
    now.n=n,now.m=n-1,now.isDir=false,now.isCon=true,now.isRep=false,now.typ=3;
    now.isVal=(rdMin!=1ll || rdMax!=1ll);
    for(int i=1;i<=n;++i) if(res[i]!=root) now.Addedge(root,res[i],RandInt(rdMin,rdMax));
    return now;
}
int RandBinaryCounter,rdbt_mch[Maxlen+5],rdbt_fa[Maxlen+5];
rdString RandBinaryString;
rdArray RandBinaryRange;
inline int BuildBinaryTree(int l,int r) // 递归建树
{
    if(l>r) return 0;
    int pos=++RandBinaryCounter;
    if(rdbt_mch[l]<=r)
    {
        int res=BuildBinaryTree(l+1,rdbt_mch[l]-1);
        rdbt_fa[RandBinaryRange(res)]=RandBinaryRange(pos);
    }
    if(rdbt_mch[l]<r)
    {
        int res=BuildBinaryTree(rdbt_mch[l]+1,r);
        rdbt_fa[RandBinaryRange(res)]=RandBinaryRange(pos);
    }
    return pos;
}
rdTree RandBinaryTree(int n,ll rdMin=1,ll rdMax=1) // 构造随机二叉树
{
    assert(n>=1 && rdMin<=rdMax);
    rdTree now;
    now.n=n,now.m=n-1,now.isDir=false,now.isCon=true,now.isRep=false,now.typ=4;
    now.isVal=(rdMin!=1ll || rdMax!=1ll);
    RandBinaryString=RandBrac(n*2);
    RandBinaryRange=RandRange(n);
    RandBinaryCounter=0;
    int st[n+5],top=0;
    for(int i=1;i<=n*2;++i)
    {
        if(RandBinaryString(i)==0) st[++top]=i;
        else rdbt_mch[i]=st[top],rdbt_mch[st[top--]]=i;
    }
    BuildBinaryTree(1,n*2);
    for(int i=1;i<=n;++i)
        if(i!=RandBinaryRange(1)) now.Addedge(rdbt_fa[i],i,RandInt(rdMin,rdMax));
    return now;
}