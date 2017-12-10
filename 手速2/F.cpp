#include<iostream>
using namespace std;
int num[10010];
int mp[110][110];
int main()
{
    int h, w, n;
    while (~scanf("%d%d%d", &h, &w, &n))
    {
        for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
        int r = 1, c = 1,clr=1;
        bool flag = true;
        while (clr<=n)
        {
            int cnt = num[clr];
            while (cnt)
            {
                mp[r][c] = clr;
                if (r % 2)
                {
                    c++;
                    if (c > w)
                    {
                        c = w;
                        r++;
                    }
                }
                else
                {
                    c--;
                    if (c == 0)
                    {
                        c = 1;
                        r++;
                    }
                }
                cnt--;
            }
            clr++;
        }
        for (int i = 1; i <= h; i++)
        {
            for (int j = 1; j <= w; j++)
            {
                if (j > 1) printf(" ");
                printf("%d", mp[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}