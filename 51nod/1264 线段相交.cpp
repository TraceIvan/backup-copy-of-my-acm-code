#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
    int t;
    int x1, x2, x3, x4, y1, y2, y3, y4;
    double k1, k2, b1, b2;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
        bool flag = false;
        if (x1 == x2)
        {
            if (x3 != x4)
            {
                k2 = 1.0*(y3 - y4) / (x3 - x4);
                b2 = y3 - x3*k2;
                double ymd = k2*x1 + b2;
                if (x1 >= min(x3, x4) && x1 <= max(x3, x4) && ymd >= min(y1, y2) && ymd <= max(y1, y2)) flag = true;
            }
        }
        else if (x3 == x4)
        {
            k1 = 1.0*(y1 - y2) / (x1 - x2);
            b1 = y1 - x1*k1;
            double ymd = k1*x3 + b1;
            if (x3 >= min(x1, x2) && x3 <= max(x1, x2) && ymd >= min(y3, y4) && ymd <= max(y4, y3)) flag = true;
        }
        else
        {
            k2 = 1.0*(y3 - y4) / (x3 - x4);
            b2 = y3 - x3*k2;
            k1 = 1.0*(y1 - y2) / (x1 - x2);
            b1 = y1 - x1*k1;
            double xmd = 1.0*(b2 - b1) / (k1 - k2);
            if (xmd >= min(x1, x2) && xmd <= max(x1, x2) && xmd >= min(x3, x4) && xmd <= max(x3, x4))flag = true;
        }
        if (flag)printf("Yes\n");
        else printf("No\n");
    }

    return 0;
}