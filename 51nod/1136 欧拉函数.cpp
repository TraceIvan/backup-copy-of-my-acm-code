//#include<bits/stdc++.h>
#include<iostream>
using namespace std;
//Euler函数表达通式：euler(x)=x(1-1/p1)(1-1/p2)(1-1/p3)(1-1/p4)…(1-1/pn),其中p1,p2……pn为x的所有素因数，x是不为0的整数。euler(1)=1（唯一和1互质的数就是1本身）。 
//欧拉公式的延伸：一个数的所有质因子之和是euler(n)*n / 2。
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