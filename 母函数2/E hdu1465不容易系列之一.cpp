//错排数公式：f[n] = (n - 1) * (f[n - 1] + f[n - 2]);
//也可以这么想;
//(1).f[1] = 0; f[2] = 1;
//(2).如果确定f[n - 1] 和 f[n - 2] 的话。
//f[n] 中必然包含 f[n - 1] * (n - 1)种情况。 即把新加入的一封和之前的任一一封交换，所得到的必然是错排。
//f[n] 中另一部分就是f[n - 2] * (n - 1) 即之前的 n - 1 封中有一封没有错排，把这封与新加入的一封交换进行错排。
#include<iostream>
using namespace std;
long long re[25];
void Init()
{
    re[1] = 0, re[2] = 1;
    for (int i = 3; i <= 20; i++) re[i] = (re[i - 1] + re[i - 2])*(i - 1);
}
int main()
{
    Init();
    int n;
    while (~scanf("%d", &n))
    {
        printf("%lld\n",re[n]);
    }
    return 0;
}