//#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int n, m;
vector<int>mp[1005];
int level[1005];
bool vis[1005];
queue<int>lfs;
int integ[1005];//记录分支节点
int ct[1005];//记录回溯到分支节点时的值。
void BFS(int r, int lv)
{
    level[r] = 0;
    queue<int>q;
    q.push(r);
    vis[r] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        int sz = mp[u].size();
        bool flag = true;
        bool biger = false;
        int cnt = 0;
        for (int i = 0; i<sz; i++)
        {
            int v = mp[u][i];
            if (!vis[v])
            {
                vis[v] = true;
                flag = false;
                q.push(v);
                level[v] = level[u] + 1;
                cnt++;
            }
            else
            {
                if (level[v]>level[u]) biger = true;
            }
        }
        if (flag)
        {
            if (biger) continue;
            lfs.push(u);
            //cout<<u<<endl;
        }
        else if (cnt>1)
        {
            integ[u] = cnt;
        }
    }
}
void DFS(int u, int fg)
{//fg为1，N赢；fg为2，V赢
    if (integ[u] >= 1)
    {
        integ[u]--;
        if (ct[u] == 0 && level[u] % 2 && fg % 2==0)
        {//u处V要走，fg为偶，V赢
            ct[u] = 2;
        }
        if (ct[u] == 0 && level[u] % 2 == 0 && fg % 2)
        {//u处N要走，fg为奇，N赢
            ct[u] = 1;
        }
        if (ct[u] == 0 && integ[u] == 0)
        {
            if (level[u] % 2) ct[u] = 1;//u处V要走，fg始终为奇，分支N一定赢
            else ct[u] = 2;
        }
        if (integ[u] == 0)
        {
            lfs.push(u);
        }
        return;
    }
    int sz = mp[u].size();
    for (int i = 0; i < sz; i++)
    {
        int v = mp[u][i];
        if (level[v] + 1 == level[u])
        {
            DFS(v, fg);
        }
    }
}
int solve()
{
    if (integ[1] == -1) integ[1] = 1;
    int rr = 1;
    while (lfs.size()>1||(lfs.size()==1&&lfs.front()!=1))
    {//fg为1，N赢；fg为2，V赢
        int sz = lfs.size();
        while (sz--)
        {
            int u = lfs.front();
            lfs.pop();
            if(rr==1)DFS(u, level[u]%2);//如果叶子为奇，V要走，N赢,fg为1
            else DFS(u, ct[u]);
        }
        rr++;
    }
    int u = lfs.front();
    lfs.pop();
    return ct[u];
}
int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        mp[u].push_back(v);
        mp[v].push_back(u);
    }
    memset(integ, -1, sizeof(integ));
    vis[1] = true;
    BFS(1, 0);

    int ans = solve();
    if (ans % 2) printf("Vladimir\n");
    else printf("Nikolay\n");
    return 0;
}
