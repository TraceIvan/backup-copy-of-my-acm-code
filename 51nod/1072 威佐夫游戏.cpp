#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int spc[4002000];
bool vis[4002000];
int main()
{
    int k = 1;
    memset(spc, 0, sizeof(spc));
    memset(vis, true, sizeof(vis));
    for (int i = 1; i <= 2000000; i++)
    {//��һ������Ծ���(0,0),(1,2),(3,5),(4,7),(6,10)...�ذܣ����Ǵ˹��ɵľ��ƿ���ͨ��һ����ﵽ���־���
        //�ص㣺(x,y)xΪǰ��δ���ֵ���Сֵ;�þ���Ϊ��(y-x+1)��
        if (vis[i])
        {
            spc[i] = i + k;
            vis[spc[i]] = false;
            k++;
        }
    }
    int t;
    scanf("%d", &t);
    int a, b;
    while (t--)
    {
        scanf("%d%d", &a, &b);
        if (a>b)
            swap(a, b);
        if (spc[a] == b)
            printf("B\n");
        else
            printf("A\n");
    }
    return 0;
}