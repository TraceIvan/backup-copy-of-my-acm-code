#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 1010;
bool mp[maxn][maxn];
int L_match[maxn], R_match[maxn], visL[maxn], visR[maxn];
int n, nl, nr;
bool dfs(int lx)
{
    visL[lx] = true;
    for (int ly = 1; ly <= nr; ly++)
    {
        if (mp[lx][ly] && !visR[ly])
        {
            visR[ly] = true;
            if (!R_match[ly] || dfs(R_match[ly]))
            {//�����ǰ��lyû�б�ƥ�䣬�����Ѿ�ƥ�䵫�Ǻ�lyƥ���lx'�ܹ�������ly'ƥ�䣬��ô��ǰly��lx�Ϳ���ƥ��
                L_match[lx] = ly;
                R_match[ly] = lx;
                return true;
            }
        }
    }
    return false;
}

int maxmatch_XYL()
{
    int ans = 0;
    memset(L_match, 0, sizeof(L_match));
    memset(R_match, 0, sizeof(R_match));
    for (int i = 1; i <= nl; i++)
    {
        memset(visL, 0, sizeof(visL));
        memset(visR, 0, sizeof(visR));
        if (dfs(i)) ans++;
    }
    return ans;
}
int main()
{
    while (~scanf("%d%d%d", &nl, &nr, &n))
    {
        if (nl == 0 && nr == 0 && n == 0) break;
        memset(mp, 0, sizeof(mp));
        for (int i = 1; i <= n; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            mp[x][y] = true;
        }
        int ans = maxmatch_XYL();
        printf("%d", ans);
        //Ѱ����С�㸲�Ǽ������
        memset(visL, 0, sizeof(visL));
        memset(visR, 0, sizeof(visR));
        //�ӵ�ǰδƥ���lx��ʼdfs,����б�a��˵��ԭ���������С�㸲�Ǽ�<����ƥ���lx>���ܸ��ǵ���ǰdfs������һ���ߣ�����ôԭ���ͱ�a���ӵ�lx'�����Ϊa�����ӵ�ly'
        for (int i = 1; i <= nl; i++) if (!L_match[i]) dfs(i);
        for (int i = 1; i <= nl; i++) if (!visL[i]) printf(" r%d", i);//�ڳ��ڼ������С�㸲�Ǽ�������ɾ�ĵ�
        for (int i = 1; i <= nr; i++) if (visR[i]) printf(" c%d", i);//��dfs������lx'�����ɵ�ly'
        printf("\n");
    }
    return 0;
}