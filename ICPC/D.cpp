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
int integ[1005];//��¼��֧�ڵ�
int ct[1005];//��¼���ݵ���֧�ڵ�ʱ��ֵ��
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
{//fgΪ1��NӮ��fgΪ2��VӮ
    if (integ[u] >= 1)
    {
        integ[u]--;
        if (ct[u] == 0 && level[u] % 2 && fg % 2==0)
        {//u��VҪ�ߣ�fgΪż��VӮ
            ct[u] = 2;
        }
        if (ct[u] == 0 && level[u] % 2 == 0 && fg % 2)
        {//u��NҪ�ߣ�fgΪ�棬NӮ
            ct[u] = 1;
        }
        if (ct[u] == 0 && integ[u] == 0)
        {
            if (level[u] % 2) ct[u] = 1;//u��VҪ�ߣ�fgʼ��Ϊ�棬��֧Nһ��Ӯ
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
    {//fgΪ1��NӮ��fgΪ2��VӮ
        int sz = lfs.size();
        while (sz--)
        {
            int u = lfs.front();
            lfs.pop();
            if(rr==1)DFS(u, level[u]%2);//���Ҷ��Ϊ�棬VҪ�ߣ�NӮ,fgΪ1
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
