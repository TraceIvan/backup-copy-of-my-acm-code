#include<iostream>
#include<memory.h>
using namespace std;
const int maxv = 125010;
int re[maxv];
int p1[maxv];
int p2[maxv];
int xx[55];
int main()
{
    int n;
    while (~scanf("%d",&n))
    {
        if (n < 0) break;
        int total = 0;
        memset(xx, 0, sizeof(xx));
        for (int i = 1; i <= n; i++)
        {
            int v, w;
            scanf("%d%d", &v, &w);
            xx[v] += w;
            total += v*w;
        }
        int totalv= total/2;
        int st;
        for (st = 0;xx[st]==0; st++);
        memset(re, 0, sizeof(re));
        memset(p1, 0, sizeof(p1));
        memset(p2, 0, sizeof(p2));

        for (int i = 0; i <= totalv; i+=st)
        {
            p1[i] = 1;
        }
        for (int i = 2; i <= 50; i++)
        {
            if (xx[i] == 0) continue;
            for (int k = 0; k <= xx[i] && k*i <=totalv; k++) p2[k*i] = 1;
            for (int j = 0; j <= totalv; j++)
            {
                for (int k = 0; k <= xx[i]&& i*k + j<=totalv; k++)
                {//第i个字符的多项式，每项的指数为i*k，系数为1
                    re[i*k + j] += p1[j] * p2[k*i];
                }
            }
            memcpy(p1, re, sizeof(re));
            memset(re, 0, sizeof(re));
            memset(p2, 0, sizeof(p2));
        }
        int ans = totalv;
        while (p1[ans] == 0) ans--;
        printf("%d %d\n", total - ans, ans);
    }
    return 0;
}