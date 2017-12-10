#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn = 1000100;
bool isp[maxn];
int prime[maxn], cnt;
void makePrime()
{
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
}
int main()
{
    makePrime();
    int n;
    while (~scanf("%d", &n))
    {
        int pos = lower_bound(prime, prime + cnt, n) - prime;
        while (!isp[pos + 1]) pos++;
        printf("%d\n", prime[pos]);
    }
    return 0;
}