//题意：有n个人，询问m次，每次求第bj+1小的数
// nth_element(arr,arr+x,arr+n);

//可以将x在[0, n]范围内，将第x小的数字移动到arr[x]上，其余比arr[x]大的，在x后面，比arr[x]小的，在x前面。（从0计数，即当x=0时，为最小的数）
//选G++，C++超时
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define LL long long
#define MXN 10000005
#define MXM 105
struct Node
{
    int w;
    int id;
    bool operator <(const Node b) const
    {
        return w<b.w;
    }
}num[MXM];
LL prt[MXM];
LL Data[MXN];
bool vis[MXN];

int n, m;
unsigned x, y, z;
unsigned rng61()
{
    LL t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;
    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;
    return z;
}

int main()
{
    int cnt = 1;
    while (scanf("%d%d%u%u%u", &n, &m, &x, &y, &z) != EOF)
    {
        for (int i = 0; i<m; i++)
        {
            scanf("%d", &num[i].w);
            num[i].id = i;
        }
        sort(num, num + m);

        for (int i = 0; i<n; i++)
            Data[i] = (LL)rng61();

        memset(vis, 0, sizeof(vis));

        for (int i = m - 1; i >= 0; i--)
        {
            if (i == m - 1)
                nth_element(Data, Data + num[i].w, Data + n);
            else
                nth_element(Data, Data + num[i].w, Data + num[i + 1].w);
            prt[num[i].id] = Data[num[i].w];
        }
        printf("Case #%d:", cnt++);
        for (int i = 0; i<m; i++)
            printf(" %lld", prt[i]);
        printf("\n");
    }
    return 0;
}