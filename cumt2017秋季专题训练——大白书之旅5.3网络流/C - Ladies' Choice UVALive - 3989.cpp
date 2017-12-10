//稳定婚姻问题

#include<iostream>
#include<queue>
#include<cstdio>
using namespace std;
const int maxn = 1010;

struct gs//Gale - Shapley算法
{//女士优先
    int n;
    int girl_pre[maxn][maxn];
    int boy_pre[maxn][maxn];
    int girl_match[maxn], boy_match[maxn];
    int next[maxn];
    queue<int>q;//未开始选择的女孩

    void engage(int girl, int boy)
    {//匹配
        int pre = boy_match[boy];
        if (pre)
        {
            girl_match[pre] = 0;
            q.push(pre);
        }
        girl_match[girl] = boy;
        boy_match[boy] = girl;
    }

    void read()
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++) scanf("%d", &girl_pre[i][j]);
            next[i] = 1;//下次等待选择
            girl_match[i] = 0;
            q.push(i);//加入未选择的女生队列
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                int p;
                scanf("%d", &p);
                boy_pre[i][p] = j;//在i男生心中p女孩的排名
            }
            boy_match[i] = 0;
        }
    }

    void solve()
    {
        while (!q.empty())
        {
            int girl = q.front();
            q.pop();
            int boy = girl_pre[girl][next[girl]++];
            if (!boy_match[boy]) engage(girl, boy);//如果该女孩喜欢的男孩没有被选
            else if (boy_pre[boy][girl] < boy_pre[boy][boy_match[boy]]) engage(girl, boy);//或者该女孩喜欢的男孩的当前匹配的女孩喜欢程度不及该女孩
            else q.push(girl);//等待下次匹配
        }
    }

    void print()
    {
        for (int i = 1; i <= n; i++) printf("%d\n", girl_match[i]);
    }

}GS;
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        GS.read();
        GS.solve();
        GS.print();
        if (t) printf("\n");
    }


    return 0;
}