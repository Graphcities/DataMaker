## 数据生成器食用指南

### 如何生成测试数据

```
<Data>
<Examples>
<Program>
make.cpp
makedata.hpp
```

`<Data>` 存放输入输出数据。

`<Examples>` 存放一些数据生成器的例子。

`<Program>` 存放你的标程 `std.cpp`（建议 `std.exe` 一起带上）

`make.cpp` 即为你的数据生成器。

`makedata.hpp` 为数据生成器的核心文件，包括输入输出，随机等底层函数。

生成测试数据的步骤如下：

1. 编写标程，命名为 `std.cpp`，存放至 `<Program>` 文件夹中。
2. 编写数据生成器 `make.cpp`。
3. 执行数据生成器，`<Data>` 文件夹中即为数据。

接下来将简要介绍 `makedata.hpp` 中的结构和函数：

---

### RandInt 类

`long long RandInt(long long l=1,long long r=1ll*1e9)` 

随机生成一个 $$[l,r]$$ 范围内的整数。

`double Randec(double l=1,double r=1e9,int digit=2)`

根据 `RandInt()` 随机生成一个 $$[l,r]$$ 范围内，精度为 `digit` 位的实数。

### Random Array 类

`const int Maxlen=2e6+5;`

随机数列最大长度。

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

构造一个随机字符串，字符集为字母表的 $$[rdMin,rdMax]$$ 位置。

`rdString RandSpeStr(int n,int rdsiz,char rdletter[])`

构造特殊字符集字符串。

### Stream 类

`void SetDataName(char dname[])`

设置输入输出文件名。

`void SetDataID(int dID)`

设置当前数据编号。

`void MakeExe()`

编译 `std.cpp`。（编译指令为 `g++ file.cpp -o file --std=c++11 -O2` ）

`void GetIn()`

开始文件输入。

`void GetOut()`

结束文件输入，执行文件输出，中途执行 `std.exe`。

