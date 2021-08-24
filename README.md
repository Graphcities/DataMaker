## 数据生成器食用指南

### 如何生成测试数据 & 对拍

```
<Data>
<Examples>
<Program>
make.cpp
makedata.hpp
```

`<Data>` 存放输入输出数据。

`<Examples>` 存放一些数据生成器和对拍程序的例子。

`<Program>` 存放你的标程 `std.cpp`（建议 `std.exe` 一起带上），对拍文件 `match.cpp` （建议 `match.exe` 一起带上），对拍数据 `match.out` 和对拍结果 `result.txt`。

`make.cpp` 即为你的数据生成器。

`makedata.hpp` 为数据生成器的核心文件，包括输入输出，随机等底层函数。

生成测试数据的步骤如下：

1. 编写标程，命名为 `std.cpp`，存放至 `<Program>` 文件夹中。
2. 编写数据生成器 `make.cpp`。
3. 执行数据生成器，`<Data>` 文件夹中即为数据。

对拍的步骤如下：

1. 编写标程 `std.cpp` 和对拍程序 `match.cpp`，存放至 `<Program>` 文件夹中。
2. 编写数据生成器 `make.cpp`。
3. 执行数据生成器，`<Program>` 文件夹中的 `result.txt` 即为对拍结果。（ 编码为 **GBK** ）

程序对拍示例放在 `<Program>` 文件夹中的 `P3379.cpp`。

接下来将简要介绍 `makedata.hpp` 中的结构和函数：

---

### Const 类

`const int Maxlen=2e6+5;`

随机数列 / 随机图的最大长度。

`const double PI=acos(-1);`

圆周率。

`const double E=exp(1);`

自然对数。

`char ALPHABET_SMALL[]="abcdefghijklmnopqrstuvwxyz";`

小写字母表。

`char ALPHABET_CAPITAL[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";`

大写字母表。

`char ALPHABET[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";`

字母表。

`char NUMBERS[]="0123456789";`

十进制数位表。

`char ZEROANDONE[]="01";`

二进制数位表。

### RandInt 类

`long long RandInt(long long l=1,long long r=1ll*1e9)` 

随机生成一个 ![](http://latex.codecogs.com/gif.latex?[l,r]) 范围内的整数。

`double Randec(double l=1,double r=1e9,int digit=2)`

根据 `RandInt()` 随机生成一个 ![](http://latex.codecogs.com/gif.latex?[l,r]) 范围内，精度为 `digit` 位的实数。

### Random Array 类

```cpp
struct rdArray
{
    int n,typ;
    long long rdMin,rdMax;
    long long isDiff;
    long long rdlist[Maxlen];
    void Shuffle();
    void Insert(int p,ll k);
    void Delete(int p);
};
```

分别为长度，种类，最小值，最大值，是否互不相同，数列，洗牌函数，插入函数，删除函数。

接下来是 `rdArray` 中函数的具体功能：

`long long& operator()(int x) {...}`

重载括号，根据下标指向随机数列的数字。

`void Shuffle()`

重排列整个数列，时间复杂度与数列长度相关。

`void Insert(int p,long long k)`

在 `p` 位置插入数 `k`，时间复杂度与数列长度相关。

`void Delete(int p)`

删除 `p` 位置的数，时间复杂度与数列长度相关。

`std::ostream &operator<<(std::ostream &out,const rdArray &now)`

重定义输出流，输出整个数列。

```cpp
struct rdString:rdArray
{
    int rdsiz;
    char rdletter[50];
};
```

`rdString` 继承自 `rdArray`，实现随机字符串。`rdsiz` 为字符集大小，`rdletter[]` 为字符集。

`std::ostream &operator<<(std::ostream &out,const rdString &now)`

重定义输出流，输出整个字符串。

接下来是关于随机数列的构造函数：

`rdArray RandArray(int n,long long rdMin=1,long long rdMax=1ll*1e9,bool isDiff=false)`

构造一个随机数列。

`rdArray RandRange(int n)`

根据 `rdArray.Shuffle()` 构造一个随机排列。

`rdString RandString(int n,long long rdMin=0,long long rdMax=25)`

构造一个随机字符串，字符集为字母表的 ![](http://latex.codecogs.com/gif.latex?[rdMin,rdMax]) 位置。

`rdString RandSpeStr(int n,int rdsiz,char rdletter[])`

构造特殊字符集字符串。

`rdString RandBrac(int n)`

构造一个长为 ![](http://latex.codecogs.com/gif.latex?n) 的随机括号序列。

### Stream 类

`void SetDataName(char dname[])`

设置输入输出文件名。

`void SetDataID(int dID)`

设置当前数据编号。

`void MakeExe()`

编译 `std.cpp`。（编译指令为 `g++ file.cpp -o file --std=c++11 -O2` ）

`void MakeMatchExe()`

编译 `match.cpp`。

`void GetIn()`

开始文件输入。

`void GetOut()`

结束文件输入，执行文件输出，中途执行 `std.exe`。

`void Match()`

生成对拍文件 `match.out`。

`void CheckFile(int AllID)`

检查文件，开始对拍。

`void ClearFile(int AllID)`

清除对拍文件 `match.out`。

### Random Graph 类

`struct Link{int frm,to,nxt; long long w;};`

邻接表存边。

```cpp
struct rdGraph
{
    int n,m,tot,Head[Maxlen],fa[Maxlen];
    long long rdMin,rdMax;
    bool isDir,isCon,isRep,isVal;
    Link Edge[Maxlen*2];
    int Find(int x);
    void Addedge(int x,int y,ll z);
    bool isConnect(int x,int y);
};
```

第一行：点数，边数，邻接表开头，并查集父亲。

第二行：边权最小值和最大值。

第三行：是否有方向，是否连通，是否有重边和自环，是否有边权。

第四行：邻接表。

第五行：并查集找祖先的函数。

第六行：加边函数。

第七行：查询是否连通的函数。

```cpp
struct rdTree:rdGraph
{
    int typ;
};
```

`rdTree` 继承自 `rdGraph`，多了一个表示类别的 `typ` 变量。

接下来是关于随机图的构造函数：

`rdGraph RandGraph(int n,int m,bool isDir=false,bool isCon=false,bool isRep=false,long long rdMin=1,long long rdMax=1)`

构造一个 ![](http://latex.codecogs.com/gif.latex?n) 点 ![](http://latex.codecogs.com/gif.latex?m) 边的随机图。

`rdGraph RandHackSPFA(int n,int m,bool isDir=false,long long rdMin=1,long long rdMax=1)`

构造一个卡 SPFA 的随机图。

`rdGraph RandDAG(int n,int m,long long rdMin=1,long long rdMax=1)`

构造一个随机的 DAG。

`rdTree RandTree(int n,long long rdMin=1,long long rdMax=1)`

利用 Prufer 序列构造一棵随机树，相当于 `RandGraph(n,n-1,false,true)`。

`rdTree RandBranch(int n,int branch=int(1e9),long long rdMin=1,long long rdMax=1)`

构造一棵叉数为 `branch` 的随机树，数据较弱。

`rdTree RandChain(int n,bool isSorted=true,long long rdMin=1,long long rdMax=1)`

构造一条随机的链，相当于 `RandBranch(n,1)`。

`rdTree RandFlower(int n,int root=1,long long rdMin=1,long long rdMax=1)`

构造一个随机的菊花图，相当于 `RandBranch(n,n-1)`。

`rdTree RandBinaryTree(int n,long long rdMin=1,long long rdMax=1)`

利用括号序列构造一棵随机的二叉树，较 `RandBranch(n,2)` 数据稍强。

---

### Refrences

- https://mivik.blog.luogu.org/the-art-of-randomness
- https://blog.csdn.net/qq_45721135/article/details/102472101
- https://github.com/luogu-dev/cyaron
- https://optmize-2.blog.luogu.org/How-to-use-Crayon

