#include<iostream>
#include<queue>
using namespace std;
const int maxn = 10005;
bool isp[maxn];
int prime[maxn], cnt;
int ans;
void makePrime()
{
    memset(isp, true, sizeof(isp));
    isp[0] = isp[1] = false;
    cnt = 0;
    for (int i = 2; i < maxn; ++i)
    {
        if (isp[i])//是素数
        {
            prime[cnt++] = i;//保存该素数
        }
        for (int j = 0; j < cnt && i * prime[j] < maxn; ++j)
        {
            isp[i * prime[j]] = false;//当前的数乘以所有已算出的素数都不是素数
            if (i % prime[j] == 0)//如果i能被某一个最小的素数整除，则退出
            {
                break;
            }
        }
    }
}
int a, b;
int vis[maxn];

void BFS()
{
    queue<int>q;
    q.push(a);
    vis[a] = 1;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        //printf("%d %d\n", v, vis[v]);
        if (v == b)
        {
            ans = vis[v]-1;
            return;
        }
        int base1 = 10,base2=1;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j <= 9; j++)
            {
                if (v%base1 / base2 == j)continue;
                if (i == 3 && j == 0)continue;
                int tmp = v / base1*base1 + v%base2 + j*base2;
                if (isp[tmp]&&!vis[tmp])
                {
                    vis[tmp] = vis[v]+1;
                    q.push(tmp);
                    
                }
            }
            base1 *= 10;
            base2 *= 10;
        }
    }
    
}
int main()
{
    makePrime();
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &a, &b);
        memset(vis, 0, sizeof(vis));
        BFS();
        printf("%d\n", ans);
    }
    return 0;
}