#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 10010;
const int INF = 0x7fffffff;
int sys[maxn];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        int cnt = 0;
        for (int i = 1; i <= n; i++)
        {
            int h;
            scanf("%d", &h);
            bool flag = false;
            int pos = 0;
            int mindis = INF;
            for (int i = 0; i < cnt; i++)
            {
                if (sys[i] >= h)//找到当前拦截系统高度与导弹高度最接近的去拦截
                {
                    if (sys[i] - h < mindis)
                    {
                        mindis = sys[i] - h;
                        pos = i;
                        flag = true;
                    }
                }
            }
            if (flag) sys[pos] = h;
            else
            {
                sys[cnt++] = h;
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}