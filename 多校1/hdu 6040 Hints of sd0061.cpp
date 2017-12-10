//���⣺��n���ˣ�ѯ��m�Σ�ÿ�����bj+1С����
// nth_element(arr,arr+x,arr+n);

//���Խ�x��[0, n]��Χ�ڣ�����xС�������ƶ���arr[x]�ϣ������arr[x]��ģ���x���棬��arr[x]С�ģ���xǰ�档����0����������x=0ʱ��Ϊ��С������
//ѡG++��C++��ʱ
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