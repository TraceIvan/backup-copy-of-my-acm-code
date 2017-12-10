#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 10010;
int w[maxn];
int n,m;
bool Cmp(int a, int b)
{
    return a > b;
}
int main()
{
    while (~scanf("%d%d", &n,&m))
    {
        for (int i = 0; i < n; i++) scanf("%d", &w[i]);
        sort(w, w + n, Cmp);
        int ans = 0;
        int pos1 = 0, pos2 = n - 1;
        while (pos1 < pos2)
        {
            if (w[pos1] + w[pos2] > m)
            {
                ans++;
                pos1++;
            }
            else
            {
                ans++;
                pos2--;
                pos1++;
            }
        }
        if (pos1 == pos2) ans++;
        printf("%d\n", ans);
    }
    return 0;
}