//��ǰ׺��(mod n)�������
//1.�����Щ������һ��0����ô���Ǳ�õ�����
//2.������Щ���б�����������ȵģ�����ԭ�����������Ϊ0��������ҵ�������Ҫ�ġ�
//���ó���ԭ����ΪN�ı�����A[i]�е�����һ����modN ������[1, N - 1] Ȼ���N�����ӵ���Щ��N - 1��������ض���������һ��������������������һ�����ˡ�
#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 50010;
int num[maxn];
long long presum[maxn];
int vis[maxn];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        memset(vis, 0, sizeof(vis));
        presum[0] = 0;
        int l=1 ,r = 1;
        bool flag = false;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &num[i]);
            presum[i] = (presum[i - 1] + num[i])%n;
            if (flag) continue;
            if (presum[i] == 0)
            {
                flag = true;
                l = 1, r = i;
            }
            else if (vis[presum[i]])
            {
                l = vis[presum[i]] + 1;
                r = i;
                flag = true;
            }
            vis[presum[i]] = i;
        }
        printf("%d\n", r - l + 1);
        for (int i = l; i <= r; i++) printf("%d\n", num[i]);
    }
    return 0;
}