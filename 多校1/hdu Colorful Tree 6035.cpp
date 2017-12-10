//#include <bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<memory.h>
#include<vector>
using namespace std;
const int MAXN = 2e5 + 10;
typedef long long LL;

//����ַ
//http://blog.csdn.net/Bahuia/article/details/76141574
LL color[MAXN], sz[MAXN], sum[MAXN], vis[MAXN]; //sum[i]��¼���ǵ��ﵱǰ�ڵ�ʱ����ɫΪi�ĸ߶����һ�����Ϊ����������С�ܺ�
                                                //sz��ȫ���ڵ���
vector <int> tree[MAXN];
LL ans;

LL dfs(int u, int pa)
{
    sz[u] = 1;
    LL allson = 0;
    int cnt = tree[u].size();
    for (int i = 0; i < cnt; i++)
    {
        int v = tree[u][i];
        if (v == pa) continue;
        LL last = sum[color[u]];            // ����ݹ�֮ǰ��sumֵ
        sz[u] += dfs(v, u);
        LL add = sum[color[u]] - last;      // add���ǽ��vΪ������������ɫΪcolor[u]�Ҹ߶���ߵ����������Ĵ�С
                                            // ���ڽ��v��˵��sz[v]-add����v����������϶˵ģ��Ҳ�������ɫΪcolor[u]����ͨ���С
        ans += (sz[v] - add) * (sz[v] - add - 1) / 2;  // �������ͨ���������������·������������ɫcolor[u]
        allson += sz[v] - add;          // allson��¼�¶��ӽ��v��ɵĲ�����ɫcolor[u]����ͨ���С�ܺ�
    }
    sum[color[u]] += allson + 1;        // sum���£���ʱҪ���ϲ���color[u]��ͨ��Ĵ�С�ܺ��Լ�u�Լ�
    return sz[u];
}

int main()
{
    //freopen("data2.in", "r", stdin);
    int n, cs = 0;
    while (scanf("%d", &n) != EOF)
    {
        memset(vis, 0, sizeof(vis));
        memset(sum, 0, sizeof(sum));
        int cnt = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%I64d", &color[i]);
            if (!vis[color[i]]) ++cnt;
            vis[color[i]] = 1;
            tree[i].clear();
        }
        for (int i = 1; i < n; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            tree[u].push_back(v);
            tree[v].push_back(u);
        }
        printf("Case #%d: ", ++cs);
        if (cnt == 1)
        {             // ֻ��һ����ɫ���������
            printf("%I64d\n", (LL)n * (n - 1LL) / 2LL);
            continue;
        }
        ans = 0;
        dfs(1, -1);
        for (int i = 1; i <= n; i++)
        {      // ע�����Ҫ��������������������ɫʣ�µ���ͨ��
            if (!vis[i]) continue;
            else
            {
                ans += (n - sum[i]) * (n - sum[i] - 1LL) / 2LL;//�����µ�ͳ�����ˣ�Ȼ��ͳ�Ʒ�������
            }
        }
        printf("%I64d\n", (LL)n * (n - 1LL) / 2LL * cnt - ans);
    }
    return 0;
}