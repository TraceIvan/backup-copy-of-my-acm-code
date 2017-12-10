#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;
const int maxn = 5005;
struct node
{
    int id;
    int xl, yl, xr, yr;
    int x, y;
}ch[maxn];
bool vis[maxn];
int n;
bool flag = true;
void CalX()
{
    memset(vis, 0, sizeof(vis));
    int r = 1;
    for (int i = 0; i < n; i++)
    {
        int minr = maxn;
        int pos;
        for (int j = 0; j < n; j++)
        {
            if (!vis[j] && ch[j].xl <= r&&ch[j].xr >= r&&ch[j].xr < minr)
            {
                minr = ch[j].xr;
                pos = j;
            }
        }
        if (minr == maxn)
        {
            flag = false;
            return;
        }
        vis[pos] = true;
        ch[pos].x = r;
        r++;
    }
}
void CalY()
{
    memset(vis, 0, sizeof(vis));
    int c = 1;
    for (int i = 0; i < n; i++)
    {
        int minc = maxn;
        int pos;
        for (int j = 0; j < n; j++)
        {
            if (!vis[j] && ch[j].yl <= c&&ch[j].yr >= c&&ch[j].yr < minc)
            {
                minc = ch[j].yr;
                pos = j;
            }
        }
        if (minc == maxn)
        {
            flag = false;
            return;
        }
        vis[pos] = true;
        ch[pos].y = c;
        c++;
    }
}
int main()
{
    while (cin >> n, n != 0)
    {
        flag = true;
        for (int i = 0; i < n; i++)
        {
            cin >> ch[i].xl >> ch[i].yl >> ch[i].xr >> ch[i].yr;
            ch[i].id = i + 1;
        }
        CalX();
        if(flag) CalY();
        if (flag)
        {
            for (int i = 0; i < n; i++)
            {
                cout << ch[i].x << ' ' << ch[i].y << endl;
            }
        }
        else cout << "IMPOSSIBLE\n";
    }
    return 0;
}