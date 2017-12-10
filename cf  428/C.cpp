#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
long long cnt;
double ttlen;
vector<int>mp[100010];
bool vis[100010];
int n;
struct node
{
    int v;
    int cnt;
    double r;
    node(int vv=0,int cc=0,double rr=0):v(vv),cnt(cc),r(rr){ }
};
void BFS()
{
    queue<node>q;
    q.push(node(1, 0,1));
    vis[1] = true;
    while (!q.empty())
    {
        node u = q.front();
        q.pop();
        int sz = mp[u.v].size();
        bool flag = true;
        int tt = 0;
        for (int i = 0; i < sz; i++)
        {
            if (!vis[mp[u.v][i]]) tt++;
        }
        for (int i = 0; i < sz; i++)
        {
            int v = mp[u.v][i];
            if (!vis[v])
            {
                flag = false;
                vis[v] = true;
                q.push(node(v, u.cnt + 1,u.r/tt));
            }
        }
        if (flag)
        {
            cnt++;
            ttlen += u.cnt*u.r;
        }
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n-1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        mp[u].push_back(v);
        mp[v].push_back(u);
    }
    BFS();
    printf("%.15lf\n",ttlen);
    return 0;
}