#include <iostream>
#include <cstring>

using namespace std;

int n;

int MOD(int a, int b)
{//ȡ��
    return a - a / b * b;
}

int miu(int n)
{
    int cnt, k = 0;
    for (int i = 2; i * i <= n; i++)
    {
        if (MOD(n, i))
        {
            continue;
        }
        cnt = 0;
        k++;
        while (MOD(n, i) == 0)
        {
            n /= i;
            cnt++;
        }
        if (cnt >= 2)
        {//����ƽ������ֵΪ0
            return 0;
        }
    }
    if (n != 1)
    {//������
        k++;
    }
    return MOD(k, 2) ? -1 : 1;//���������ӣ�-1������1
}

int main()
{
    while (~scanf("%d",&n))
    {
        printf("%d\n",miu(n));
    }
    return 0;
}