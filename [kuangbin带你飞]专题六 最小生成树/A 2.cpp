#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n;
const int maxn = 30;
struct node
{
    int to;
    int len;
    node(int tt=0,int ll=0):to(tt),len(ll){ }
    friend bool operator <(const node&a, const node&b)
    {
        return a.len > b.len;
    }
};
vector<node>mp[maxn];
vector<node>minheap;
bool vis[maxn];
bool Cmp(int a, int b)
{
    return a > b;
}
int Prime()
{
    memset(vis, 0, sizeof(vis));
    minheap.clear();
    int cnt = 1;
    vis[0] = true;
    int sz = mp[0].size();
    for (int i = 0; i < sz; i++)
    {
        minheap.push_back(mp[0][i]);
    }
    make_heap(minheap.begin(), minheap.end());
    node tmp;
    int ans = 0;
    while (cnt < n)
    {
        do
        {
            pop_heap(minheap.begin(), minheap.end());
            tmp = minheap.back();
            minheap.pop_back();
        } while (vis[tmp.to]);
        ans += tmp.len;
        cnt++;
        int u = tmp.to;
        vis[u] = true;
        int sz = mp[u].size();
        for (int i = 0; i < sz; i++)
        {
            if (vis[mp[u][i].to])continue;
            minheap.push_back(mp[u][i]);
            push_heap(minheap.begin(), minheap.end());
        }

    }
    return ans;
}
int main()
{
    while (~scanf("%d", &n))
    {
        if (n == 0)break;
        for (int i = 0; i <= n; i++) mp[i].clear();
        char v1, v2;
        int len;
        int k;
        for (int i = 0; i < n - 1; i++)
        {

            cin >> v1;
            scanf("%d", &k);
            for (int j = 0; j < k; j++)
            {
                cin >> v2;
                scanf("%d", &len);
                mp[v1 - 'A'].push_back(node(v2 - 'A', len));
                mp[v2 - 'A'].push_back(node(v1 - 'A', len));
            }
        }
        int ans = Prime();
        printf("%d\n", ans);
    }
    return 0;
}