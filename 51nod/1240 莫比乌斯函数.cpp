#include <iostream>
#include <cstring>

using namespace std;

int n;

int MOD(int a, int b)
{//取余
    return a - a / b * b;
}

int miu(int n)
{
    int cnt, k = 0;
    for (int i = 2; i * i <= n; i++)
    {
        if (MOD(n, i))
        {
            continue;
        }
        cnt = 0;
        k++;
        while (MOD(n, i) == 0)
        {
            n /= i;
            cnt++;
        }
        if (cnt >= 2)
        {//存在平方数，值为0
            return 0;
        }
    }
    if (n != 1)
    {//大质数
        k++;
    }
    return MOD(k, 2) ? -1 : 1;//奇数个因子，-1；否则1
}

int main()
{
    while (~scanf("%d",&n))
    {
        printf("%d\n",miu(n));
    }
    return 0;
}