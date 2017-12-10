//欧拉函数
//对正整数n，欧拉函数是小于n的正整数中与n互质的数的数目（φ(1) = 1）
//题意：
//给一些数Ai（第 i 个数），Ai这些数代表的是某个数欧拉函数的值，我们要求出数 Ni 的欧拉函数值不小于Ai。而我们要求的就是这些 Ni 这些数字的和sum，而且我们想要sum最小，求出sum最小多少。
//解题思路：
//要求和最小，我们可以让每个数都尽量小，那么我们最后得到的肯定就是一个最小值。给定一个数的欧拉函数值ψ(N)，我们怎么样才能求得最小的N ?我们知道，一个素数P的欧拉函数值ψ(P) = P - 1。所以如果我们知道ψ(N)，那么最小的N就是最接近ψ(N)，并且大于ψ(N)的素数。我们把所有素数打表之后再判断就可以了。
#include<iostream>
#include<memory.h>
#include<cstdio>
using namespace std;
const int maxn = 1010000;
bool isp[maxn];
int prime[maxn], cnt;
int v[maxn];//对于i（欧拉函数值），存大于等于它的最小素数
void makePrime()
{
    //线性素数筛
    memset(isp, true, sizeof(isp));
    isp[0] = isp[1] = false;
    cnt = 0;
    for (int i = 2; i < maxn; ++i)
    {
        if (isp[i])//是素数
        {
            prime[cnt++] = i;//保存该素数
        }
        for (int j = 0; j < cnt && i * prime[j] < maxn; ++j)
        {
            isp[i * prime[j]] = false;//当前的数乘以所有已算出的素数都不是素数
            if (i % prime[j] == 0)//如果i能被某一个最小的素数整除，则退出
            {
                break;
            }
        }
    }
    memset(v, 0, sizeof(v));
    for (int i = 1,p=0; i <= 1000000; i++)
    {
        if (i < prime[p])v[i] = prime[p];
        else
        {
            p++;
            v[i] = prime[p];
        }
    }
}
int main()
{
    makePrime();
    int t;
    int Case = 1;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        long long sum = 0;
        for (int i = 0; i < n; i++)
        {
            int var;
            scanf("%d", &var);
            sum += v[var];
        }
        printf("Case %d: %lld Xukha\n", Case++, sum);
    }
    return 0;
}
