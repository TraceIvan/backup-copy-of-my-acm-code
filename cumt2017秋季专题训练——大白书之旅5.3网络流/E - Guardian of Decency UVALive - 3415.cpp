#include<iostream>
#include<map>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;
const int maxn = 510;
map<string, int>music;
map<string, int>sports;
struct per
{
    int h;
    bool isboy;
    int id_music;
    int id_sports;
}pp[maxn];

int n,nl, nr;
bool mp[maxn][maxn];

int l_match[maxn], r_match[maxn], visl[maxn], visr[maxn];

bool dfs(int lx)
{
    visl[lx] = true;
    for (int ly = 1; ly <= nr; ly++)
    {
        if (mp[lx][ly] && !visr[ly])
        {
            visr[ly] = true;
            if (!r_match[ly] || dfs(r_match[ly]))
            {
                l_match[lx] = ly;
                r_match[ly] = lx;
                return true;
            }
        }
    }
    return false;
}

int maxmatch_XYL()
{
    int ans = 0;
    memset(l_match, 0, sizeof(l_match));
    memset(r_match, 0, sizeof(r_match));
    for (int i = 1; i <= nl; i++)
    {
        memset(visl, 0, sizeof(visl));
        memset(visr, 0, sizeof(visr));
        if (dfs(i)) ans++;
    }
    return ans;
}

bool check(int u, int v)
{//四个条件都不满足建边
    if (abs(pp[u].h - pp[v].h) > 40)
        return false;
    else if(pp[u].isboy == pp[v].isboy)
        return false;
    else if(pp[u].id_music != pp[v].id_music)
        return false; 
    else if(pp[u].id_sports == pp[v].id_sports) 
        return false;
    else return true;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        nl = nr = n;
        memset(mp, 0, sizeof(mp));
        music.clear();
        sports.clear();
        char tmp[110];
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%s", &pp[i].h,tmp);
            if (tmp[0] == 'M') pp[i].isboy = true;
            else pp[i].isboy = false;
            scanf("%s", tmp);
            if (!music[tmp]) music[tmp] = music.size() + 1;
            pp[i].id_music = music[tmp];
            scanf("%s", tmp);
            if (!sports[tmp]) sports[tmp] = sports.size() + 1;
            pp[i].id_sports = sports[tmp];
        }
        for (int i = 1; i <= nl; i++)
        {
            for (int j = i + 1; j <= nr; j++)
            {
                if (check(i, j)) mp[i][j]=mp[j][i]=true;
            }
        }
        int ans = maxmatch_XYL();
        printf("%d\n", n-ans/2);
    }
    return 0;
}