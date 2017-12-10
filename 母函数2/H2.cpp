#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int cat[110][110];//ÿһλ��Ŵ�����4λ
//Catalan������Ϲ�ʽΪ Cn=C(2n,n) / (n+1);
//���ƹ�ʽΪ h(n) = h(n - 1)*(4 * n - 2) / (n + 1);
int length[110];//��¼ÿһλ����������λ��
const int MOD = 10000;
void Init()
{//���1~100λ��������
    memset(cat, 0, sizeof(cat));
    cat[1][0] = 1;
    int len = 1;
    length[1] = 1;
    for (int i = 2; i <= 100; i++)
    {
        //�˷�
        int r = 0;
        for (int j = 0; j < len; j++)
        {
            int temp = cat[i - 1][j] * (4 * i - 2);
            cat[i][j] = (temp+r)%MOD;
            r = (temp + r) / MOD;
        }
        //��λ
        while (r)
        {
            cat[i][len++] = r %MOD;
            r /= MOD;
        }
        //����
        r = 0;
        for (int j = len - 1; j >= 0; --j)
        {
            int temp = r * MOD + cat[i][j];
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
        printf("%d", cat[n][len - 1]);
        for (int j = len - 2; j >= 0; j--) printf("%.4d", cat[n][j]);
        printf("\n");
    }
    return 0;
}