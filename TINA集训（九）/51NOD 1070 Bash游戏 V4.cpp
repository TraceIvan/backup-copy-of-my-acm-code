//先手胜当且仅当n不是Fibonacci数
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 50;
long long fib[maxn];
int main()
{
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i <maxn; i++) fib[i] = fib[i - 1] + fib[i - 2];
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        int pos = lower_bound(fib, fib +maxn,n) - fib;
        if (fib[pos] == n)
        {
            printf("B\n");
        }
        else printf("A\n");
    }
    return 0;
}