#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = 50005;
int p[N], r[N];  //p[i],r[i]分别表示编号为i的动物的父节点，i和父节点的关系
int ans;
void Make_Par(int n)  //对每个元素的父节点初始化为自身
{
    int i;
    for (i = 0; i<n; i++)
    {
        p[i] = i;
        r[i] = 0;
    }
}
int Find_Par(int p[], int r[], int x)  //得到元素的父节点，且进行路径压缩:经过"递推"找到祖先节点后，"回溯"的时候顺便将它的子孙节点都直接指向祖先，通俗点说就是，每次通过儿子对父亲的关系，父亲对爷爷的关系，得到儿子对爷爷的关系，把儿子指向爷爷，使爷爷成为儿子的父节点
{
    int t;
    if (x == p[x])
        return x;
    else
    {
        t = p[x];
        p[x] = Find_Par(p, r, p[x]);  //递归寻找x所在集合的代表元素
        r[x] = (r[t] + r[x]) % 3;  //更新x与此时代表元的关系
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
