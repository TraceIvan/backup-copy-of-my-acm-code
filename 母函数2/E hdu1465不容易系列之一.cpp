//��������ʽ��f[n] = (n - 1) * (f[n - 1] + f[n - 2]);
//Ҳ������ô��;
//(1).f[1] = 0; f[2] = 1;
//(2).���ȷ��f[n - 1] �� f[n - 2] �Ļ���
//f[n] �б�Ȼ���� f[n - 1] * (n - 1)������� �����¼����һ���֮ǰ����һһ�⽻�������õ��ı�Ȼ�Ǵ��š�
//f[n] ����һ���־���f[n - 2] * (n - 1) ��֮ǰ�� n - 1 ������һ��û�д��ţ���������¼����һ�⽻�����д��š�
#include<iostream>
using namespace std;
long long re[25];
void Init()
{
    re[1] = 0, re[2] = 1;
    for (int i = 3; i <= 20; i++) re[i] = (re[i - 1] + re[i - 2])*(i - 1);
}
int main()
{
    Init();
    int n;
    while (~scanf("%d", &n))
    {
        printf("%lld\n",re[n]);
    }
    return 0;
}