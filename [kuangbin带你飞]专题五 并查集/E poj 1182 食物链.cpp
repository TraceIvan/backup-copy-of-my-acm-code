#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = 50005;
int p[N], r[N];  //p[i],r[i]�ֱ��ʾ���Ϊi�Ķ���ĸ��ڵ㣬i�͸��ڵ�Ĺ�ϵ
int ans;
void Make_Par(int n)  //��ÿ��Ԫ�صĸ��ڵ��ʼ��Ϊ����
{
    int i;
    for (i = 0; i<n; i++)
    {
        p[i] = i;
        r[i] = 0;
    }
}
int Find_Par(int p[], int r[], int x)  //�õ�Ԫ�صĸ��ڵ㣬�ҽ���·��ѹ��:����"����"�ҵ����Ƚڵ��"����"��ʱ��˳�㽫��������ڵ㶼ֱ��ָ�����ȣ�ͨ�׵�˵���ǣ�ÿ��ͨ�����ӶԸ��׵Ĺ�ϵ�����׶�үү�Ĺ�ϵ���õ����Ӷ�үү�Ĺ�ϵ���Ѷ���ָ��үү��ʹүү��Ϊ���ӵĸ��ڵ�
{
    int t;
    if (x == p[x])
        return x;
    else
    {
        t = p[x];
        p[x] = Find_Par(p, r, p[x]);  //�ݹ�Ѱ��x���ڼ��ϵĴ���Ԫ��
        r[x] = (r[t] + r[x]) % 3;  //����x���ʱ����Ԫ�Ĺ�ϵ
        return p[x];
    }
}
void Union(int p[], int r[], int x, int y, int rx, int ry, int d)
{
    p[ry] = rx;
    r[ry] = (r[x] - r[y] + 2 + d) % 3;
}

int main()
{
    int n, k, d, x, y, a, b;
    scanf("%d%d", &n, &k);
    Make_Par(n);
    while (k--&&scanf("%d%d%d", &d, &x, &y))
    {
        if (x>n || y>n)
            ans++;
        else
        {
            if (d == 2 && x == y)
                ans++;
            else
            {
                int rx, ry;
                rx = Find_Par(p, r, x);
                ry = Find_Par(p, r, y);
                if (rx != ry)
                    Union(p, r, x, y, rx, ry, d);
                else
                {
                    if (d == 1)
                        if (r[x] != r[y])
                            ans++;
                    if (d == 2)
                        if (((r[y] + 3 - r[x]) % 3) != 1)
                            ans++;
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
