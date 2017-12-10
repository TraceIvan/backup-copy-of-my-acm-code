#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
const int maxn = 3010;
int pre[maxn];
int f[maxn];
int level[maxn];
int n,Count;
bool flag = true;
int cnt[10];
vector<int>mp[maxn];
int Find(int x)
{
    int r = x;
    while (r != pre[r])
    {
        r = pre[r];
    }
    int i = x, j;
    while (i != r)
    {
        j = pre[i];
        pre[i] = r;
        i = j;
    }
    return r;
}
void Join(int x, int y)
{
    int fx = Find(x), fy = Find(y);
    if (fx != fy) pre[fx] = fy,Count--;
}
void DFS(int r,int lv,int fa)
{
    if (!flag) return;
    level[r] = lv;
    f[r] = fa;
    int sz = mp[r].size();
    for (int i = 0; i < sz&&flag; i++)
    {
        int u = mp[r][i];
        if (level[u] == -1) DFS(u, lv + 1,r);
        else
        {
            if (level[u] == level[r])
            {
                if (f[u] == f[r]) flag = false;
            }
            else if (level[u] + 2 == level[r]) flag = false;
        }
    }
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 0; i <= n; i++) pre[i] = i,mp[i].clear();
        Count = n;
        for (int i = 1; i <= n; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                int v;
                scanf("%d", &v);
                if (v) Join(i, j);
                if (v) mp[i].push_back(j), mp[j].push_back(i);
            }
        }
        if (n < 3)
        {
            printf("Great Team!\n");
        }
        else
        {
            if (n < 5 && Count>1)
            {
                if(Count==2) printf("Great Team!\n");
                else printf("Bad Team!\n");
            }
            else if (Count > 1) printf("Bad Team!\n");
            else
            {
                flag = true;
                int st = 1;
                while (mp[st].size() == 0) st++;
                memset(level, -1, sizeof(level));
                memset(f, -1, sizeof(f));
                DFS(st,1,0);
                if (flag) printf("Great Team!\n");
                else printf("Bad Team!\n");
            }
        }
    }
    return 0;
}