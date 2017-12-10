#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int cat[110][110];
//Catalan������Ϲ�ʽΪ Cn=C(2n,n) / (n+1);
//���ƹ�ʽΪ h(n) = h(n - 1)*(4 * n - 2) / (n + 1);
int length[110];//��¼ÿһλ����������λ��
void Init()
{//���1~100λ��������
    memset(cat, 0, sizeof(cat));
    cat[1][0] = 1;
    int len = 1;
    length[1] = 1;
    for (int i = 2; i <= 100; i++)
    {
        //�˷�
        for (int j = 0; j < len; j++)
        {
            cat[i][j] = cat[i - 1][j] * (4 * i - 2);
        }
        //��λ
        int r = 0;
        for (int j = 0; j < len; j++)
        {
            int temp = cat[i][j] + r;
            cat[i][j] = (temp) % 10;
            r = temp / 10;
        }
        while (r)
        {
            cat[i][len++] = r % 10;
            r /= 10;
        }
        //����
        r = 0;
        for (int j = len - 1; j >= 0; --j)
        {
            int temp = r * 10 + cat[i][j];
            cat[i][j] = temp / (i + 1);
            r = temp % (i + 1);
        }
        //�����������λ0����
        while (cat[i][len - 1] == 0)
        {
            len--;
        }
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
        for (int j = len - 1; j >= 0; j--) printf("%d", cat[n][j]);
        printf("\n");
    }
    return 0;
}