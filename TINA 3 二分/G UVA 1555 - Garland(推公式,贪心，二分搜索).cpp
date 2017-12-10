#include<iostream>
#include<cstdio>
using namespace std;
int n;
double A, B;
bool Judge(double x)
{//Hi=2*H(i-1)+2-H(i-2)
    double h1 = A, h2 = x,h3;
    for (int i = 3; i <= n; i++)
    {
        h3 = 2 * h2 + 2 - h1;
        if (h3 < 0) return false;
        h1 = h2, h2 = h3;
    }
    B = h3;
    return true;
}
int main()
{
    while (~scanf("%d%lf", &n, &A))
    {
        double L = 0, R = A;
        while (R - L >= 1e-6)
        {
            double mid = (R + L) / 2;
            if (Judge(mid)) R = mid;
            else L = mid;
        }
        printf("%.2lf\n", B);
    }
    return 0;
}