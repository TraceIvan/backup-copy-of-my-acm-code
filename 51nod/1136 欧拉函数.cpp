//#include<bits/stdc++.h>
#include<iostream>
using namespace std;
//Euler�������ͨʽ��euler(x)=x(1-1/p1)(1-1/p2)(1-1/p3)(1-1/p4)��(1-1/pn),����p1,p2����pnΪx��������������x�ǲ�Ϊ0��������euler(1)=1��Ψһ��1���ʵ�������1������ 
//ŷ����ʽ�����죺һ����������������֮����euler(n)*n / 2��
int euler(int n)
{
    int res = n, i;
    for (i = 2; i*i <= n; i++)
    {
        if (n%i == 0)
        {
            res = res / i*(i - 1);
            while (n%i == 0) n = n / i;
        }
    }
    if (n != 1) res = res / n*(n - 1);
    return res;
}
int main()
{
    int n;
    cin >> n;
    cout << euler(n) << endl;
    return 0;
}