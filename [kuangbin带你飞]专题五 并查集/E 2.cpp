#include<iostream>
using namespace std;
const int maxn = 50010;
int n,k;
int pre[maxn], r[maxn];
//根据“x与p[x]能否确定两者之间的关系”来划分，若能确定x与p[x]的关系，则它们同属一个集合。
//p[x]表示x的根结点。r[x]表示p[x]与x的关系。r[x] == 0 表示p[x]与x同类；1表示p[x]吃x；2表示x吃p[x]。
void Init()
{
    for (int i = 0; i <= n; i++)
    {
        pre[i] = i;
        r[i] = 0;
    }
}

//每次通过儿子对父亲的关系，父亲对爷爷的关系，得到儿子对爷爷的关系
int Find(int x)
{
    if (pre[x] == x) return x;
    else
    {
        int fa = pre[x];
        pre[x] = Find(fa);
        r[x] = (r[x] + r[fa]) % 3;
        return pre[x];
    }
}

bool Union(int x, int y, int d)
{//d=1：x和y是同类；d=2,x吃y
    int rx = Find(x), ry = Find(y);
    if (rx == ry)return true;
    else
    {
        pre[ry] = rx;
        r[ry] = (r[x] - r[y] + 2 + d) % 3;
        //r[ry]=(3-r[y]+(d-1)+r[x])%3(可推)
        return false;
    }
}

int main()
{
    scanf("%d%d", &n, &k);
    Init();
    int cnt = 0;
    while (k--)
    {
        int d, x, y;
        scanf("%d%d%d", &d, &x, &y);
        if (x > n || y > n) cnt++;
        else
        {
            bool same = Union(x, y, d);
            if (same)
            {
                if (d == 1)
                {
                    //D == 1 表示X与Y为同类，而从r[X] != r[Y]可以推出 X 与 Y 不同类。矛盾。
                    if (r[x] != r[y])
                    {
                        cnt++;
                    }
                }
                else
                {
                    if ((r[y] + 3 - r[x]) % 3 != 1)
                    {//（X 与Y为同类）或者　r[X] == ( r[Y] + 1 ) % 3 （Y吃X ）则此话为假。
                        cnt++;
                    }
                }
            }
        }
    }
    printf("%d\n", cnt);
    return 0;
}