#include<iostream>
using namespace std;
const int maxn = 50010;
int n,k;
int pre[maxn], r[maxn];
//���ݡ�x��p[x]�ܷ�ȷ������֮��Ĺ�ϵ�������֣�����ȷ��x��p[x]�Ĺ�ϵ��������ͬ��һ�����ϡ�
//p[x]��ʾx�ĸ���㡣r[x]��ʾp[x]��x�Ĺ�ϵ��r[x] == 0 ��ʾp[x]��xͬ�ࣻ1��ʾp[x]��x��2��ʾx��p[x]��
void Init()
{
    for (int i = 0; i <= n; i++)
    {
        pre[i] = i;
        r[i] = 0;
    }
}

//ÿ��ͨ�����ӶԸ��׵Ĺ�ϵ�����׶�үү�Ĺ�ϵ���õ����Ӷ�үү�Ĺ�ϵ
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
{//d=1��x��y��ͬ�ࣻd=2,x��y
    int rx = Find(x), ry = Find(y);
    if (rx == ry)return true;
    else
    {
        pre[ry] = rx;
        r[ry] = (r[x] - r[y] + 2 + d) % 3;
        //r[ry]=(3-r[y]+(d-1)+r[x])%3(����)
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
                    //D == 1 ��ʾX��YΪͬ�࣬����r[X] != r[Y]�����Ƴ� X �� Y ��ͬ�ࡣì�ܡ�
                    if (r[x] != r[y])
                    {
                        cnt++;
                    }
                }
                else
                {
                    if ((r[y] + 3 - r[x]) % 3 != 1)
                    {//��X ��YΪͬ�ࣩ���ߡ�r[X] == ( r[Y] + 1 ) % 3 ��Y��X ����˻�Ϊ�١�
                        cnt++;
                    }
                }
            }
        }
    }
    printf("%d\n", cnt);
    return 0;
}