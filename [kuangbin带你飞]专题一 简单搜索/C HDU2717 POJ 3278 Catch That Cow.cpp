#include<iostream>
#include<queue>
#include<memory.h>
using namespace std;
int n, k;
struct node
{
    int pos;
    int steps;
    node(int p=0,int stp=0):pos(p),steps(stp){ }
};
bool vis[200010];
int main()
{
    while (~scanf("%d%d", &n, &k))
    {
        //BFS();
        memset(vis, 0, sizeof(vis));
        queue<node>q;
        q.push(node(n,0));
        vis[n] = true;
        int ans = 0;
        while (!q.empty())
        {
            node t = q.front();
            q.pop();
            int pos = t.pos, stps = t.steps;
            if (pos == k)
            {
                ans = stps;
                break;
            }
            if (pos < k)
            {
                if(!vis[pos+1])q.push(node(pos + 1, stps + 1)), vis[pos + 1]=true;
                if(!vis[pos*2])q.push(node(pos * 2, stps + 1)),vis[pos*2]=true;
                if(pos-1>0&&!vis[pos-1])q.push(node(pos - 1, stps + 1)),vis[pos-1]=true;
            }
            else
            {
                if(!vis[pos-1])q.push(node(pos - 1, stps + 1)),vis[pos-1]=true;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}