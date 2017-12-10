#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    int t4 = 0;
    int tsum = 0;
    int t3 = 0, t2 = 0, t1 = 0;
    bool flag = true;
    for (int i = 1; i <= k; i++)
    {
        int num;
        scanf("%d", &num);
        t4 += num / 4;
        if (num % 4 == 3) t3++;
        else if (num % 4 == 2) t2++;
        else if(num%4==1)t1++;
        tsum += (num % 4+1)/2;
    }
    int total4 = n, total2 = 2 * n;
    if (t4 >= n)
    {
        total4 = 0;
        total2 -= (t4 - n) * 2;
        if (total2 < 0) flag = false;
        else if (tsum > total2) flag = false;
    }
    else
    {
        total4 -= t4;
        if (tsum > total2 + total4)
        {
            if (t3 <= total4)
            {
                total4 -= t3;
                if (t2 <= total2)
                {
                    total2 -= t2;
                    if (t1 > total2 + 2 * total4)flag = false;
                }
                else
                {
                    t2 -= total2;
                    total2 = 0;
                    if (t2 > total4+total4/2) flag = false;
                    else
                    {
                        if (t2 >= total4)
                        {
                            t2 -= total4;
                            if (t2 * 2 + t1 > total4) flag = false;
                        }
                        else if (t1 > t2 + (total4 - t2) * 2)flag = false;
                    }
                }
            }
            else
            {
                t3 -= total4;
                total4 = 0;
                if (total2 < t3 * 2 + t2 + t1) flag = false;
            }

        }
    }
    if (flag)printf("YES\n");
    else printf("NO\n");
    return 0;
}