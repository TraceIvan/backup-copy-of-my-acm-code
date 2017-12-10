#include<iostream>
#include<string>
using namespace std;
int st[26];
int ed[26];
bool vis[26];
int num[1000010];
int main()
{
    int n, k;
    while (~scanf("%d%d", &n, &k))
    {
        memset(ed, -1, sizeof(st));
        memset(st, 0, sizeof(st));
        memset(vis, 0, sizeof(vis));
        memset(num, 0, sizeof(num));
        string s;
        cin.get();
        getline(cin, s);
        for (int i = 0; i <n; i++)
        {
            if (!vis[s[i] - 'A'])
            {
                vis[s[i] - 'A'] = true;
                ed[s[i] - 'A']=st[s[i] - 'A'] = i;
                num[i] = 1;
            }
            else
            {
                ed[s[i] - 'A'] = i;
            }
        }
        for (int i = 0; i < 26; i++)
        {
            if(ed[i]!=-1) num[ed[i]+1] += -1;
        }
        bool flag = false;
        int cnt = 0;
        for (int i = 0;!flag&& i <= n; i++)
        {
            cnt = cnt + num[i];
            if (cnt > k) flag = true;
        }
        if (flag)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}