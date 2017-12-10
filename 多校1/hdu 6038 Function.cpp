#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdio>
using namespace std;

typedef __int64 LL;
const int maxn = 110000;
const int mod = 1e9 + 7;

int a[maxn], b[maxn];
vector<int> na, nb;
bool vis[maxn];

void findnum(int *a, int n, vector<int> &res)     //寻找 res 中的循环节个数以及长度
{
    memset(vis, false, sizeof(vis));
    for (int i = 0; i<n; i++)
    {
        if (!vis[i])
        {
            int now = a[i], len = 0;
            while (!vis[now])
            {
                ++len;
                vis[now] = true;
                now = a[now];
            }
            res.push_back(len);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int n, m, ti = 0;
    while (cin >> n >> m)
    {
        na.clear();
        nb.clear();
        for (int i = 0; i<n; i++)
            cin >> a[i];
        for (int i = 0; i<m; i++)
            cin >> b[i];
        findnum(a, n, na);
        findnum(b, m, nb);
        LL ans = 1;
        int lena = na.size();
        int lenb = nb.size();
        for (int i = 0; i<lena; i++)
        {
            LL res = 0;
            for (int j = 0; j<lenb; j++)
            {
                if (na[i] % nb[j] == 0)
                    res = (res + nb[j]) % mod;
            }
            ans = (ans*res) % mod;
        }
        cout << "Case #" << ++ti << ": " << ans << endl;
    }
    return 0;
}