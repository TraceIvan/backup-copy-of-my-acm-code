#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define LL long long
LL a, b, c, qian, hou, pp, mod = 1000000000;
LL gold[3] = { 618033988,749894848,204586834 }; //�� 0.618033988749894848204586834... ��������Ž�������
//ak =[k��1+��5��/2]��bk= ak + k ��k=0��1��2��...n �����ű�ʾȡ������)
int main()
{
    int t; scanf("%d", &t);
    while (t--)
    {
        scanf("%lld%lld", &a, &b);
        if (a>b)
            swap(a, b);
        c = b - a;
        qian = c / mod; hou = c%mod; //��10 ^ 18�ֳ�������10 ^ 9
        LL lll = hou*gold[2];//�˷�ģ��
        lll = qian*gold[2] + hou*gold[1] + lll / mod;
        lll = qian*gold[1] + hou*gold[0] + lll / mod;
        lll = c + qian*gold[0] + lll / mod;
        if (a == lll)
            printf("B\n");
        else
            printf("A\n");
    }
    return 0;
}