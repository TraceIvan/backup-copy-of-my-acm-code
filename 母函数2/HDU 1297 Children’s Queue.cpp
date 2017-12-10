//һ������n�Ķ��п��Կ���һ��n - 1�Ķ�����׷�ӵ�1��С�������С��ֻ�����ǣ�
//a.�к����κ�n - 1�ĺϷ�����׷��1���к���Ȼ�ǺϷ��ģ������Ϊf[n - 1]��
//b.Ů������ǰn - 1����Ů��Ϊĩβ�Ķ��к�׷��1λŮ��Ҳ�ǺϷ��ģ����ǿ���ת��Ϊn - 2�Ķ�����׷��2λŮ����
//һ���������n - 2�ĺϷ�������׷��2λŮ���������Ϊf[n - 2]��
//������ע�⵽������ѵ㣬����ǰn - 2λ��Ů��Ϊĩβ�Ĳ��Ϸ����У���������1λŮ����β����Ҳ����׷��2λŮ����Ϊ�Ϸ����У�������n - 2���Ϸ����б�Ȼ����n - 4�Ϸ����� + 1�к� + 1Ů���Ľṹ���������Ϊf[n - 4]��
//f[n] = f[n - 1] + f[n - 2] + f[n - 4]
#include<iostream>
#include<cstring>
using namespace std;
int f[1010][1010];
int length[1010];
void Init()
{
    memset(f, 0, sizeof(f));
    f[1][0] = 1;
    f[2][0] = 2;
    f[3][0] = 4;
    f[4][0] = 7;
    int len = 1;
    length[1] = length[2] = length[3] = length[4] = 1;
    for (int i = 5; i <= 1000; i++)
    {
        for (int j = 0; j < len; j++)
        {
            f[i][j] += f[i - 1][j] + f[i - 2][j] + f[i - 4][j];
            f[i][j + 1] += f[i][j] / 10000;
            f[i][j] %= 10000;
        }
        while (f[i][len]) len++;
        length[i] = len;
    }
}
int main()
{
    Init();
    int n;
    while (~scanf("%d", &n))
    {
        int len = length[n];
        printf("%d", f[n][len - 1]);
        for (int i = len - 2; i >= 0; i--) printf("%04d", f[n][i]);
        printf("\n");
    }
    return 0;
}