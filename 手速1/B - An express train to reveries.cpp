#include<iostream>
#include<memory.h>
using namespace std;
int a[1005];
int b[1005];
int vis[1005];
int n;
int main()
{
    while(cin >> n)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        memset(vis, -1, sizeof(vis));
        int pos1, pos2,unvis;
        for (int j = 0; j < n; j++)
        {
            cin >> b[j];
            if (vis[b[j]] > -1) pos1 = vis[b[j]], pos2 = j;
            else vis[b[j]] = j;
        }
        for (int i = 1; i <= n; i++)
        {
            if (vis[i]==-1)
            {
                unvis = i;
                break;
            }
        }
        int cnt = 0;
        if (a[pos1] == unvis) cnt++;
        if (a[pos2] == unvis) cnt++;
        if (cnt == 2)
        {
            b[pos1] = unvis;
        }
        else if (cnt == 1)
        {
            if (a[pos1] == unvis) b[pos1]=unvis;
            else b[pos2] = unvis;
        }
        else
        {
            if (a[pos1] == b[pos1]) b[pos2] = unvis;
            else b[pos1] = unvis;
        }
        for (int i = 0; i < n; i++)
        {
            if (i > 0) cout << ' ';
            cout << b[i];
        }
        cout << endl;
    }
    return 0;
}