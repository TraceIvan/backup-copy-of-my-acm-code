#include<iostream>
using namespace std;
//����d = gcd(a, b);x,y��Ӧ�ڵ�ʽax + by = d�е�x��y
long long extendGCD(long long a, long long b, long long &x, long long &y)
{
    if (a == 0 && b == 0) return -1;//�����Լ��
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    long long d = extendGCD(b, a%b, y, x);
    y -= a / b*x;
    return d;
}
//����Ԫ ax = 1(mod n)
long long modReverse(long long a, long long n)
{//Ҫ��a,n����
    long long x, y;
    long long d = extendGCD(a, n, x, y);
    if (d == 1)
    {
        return (x%n + n) % n;//��ֹΪ��
    }
    else return -1;//����Ԫ
}
int main()
{
    long long m, n;
    while (~scanf("%I64d%I64d", &m, &n))
    {//k*m%n=1=>k*m+x(-n)=1=>k*m=1(mod n)=>m����ģn�ĳ˷���ԪΪk
        printf("%I64d\n", modReverse(m, n));
    }

    return 0;
}