#include<iostream>
#include<algorithm>
#include<string.h>
#include<cstdio>
using namespace std;
char s[100100];
int num[100100];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        scanf("%s", s);
        int len = strlen(s);
        long long sum = 0;
        for (int i = 0; i < len; i++)
        {
            num[i] = s[i] - '0';
            sum += 1ll * num[i];
        }
        if (sum >= n)printf("0\n");
        else
        {
            sort(num, num + len);
            int d = n - sum;
            int cnt = 0;
            for (int i = 0; i < len; i++)
            {
                int td = 9 - num[i];
                cnt++;
                if (td >= d)
                {
                    d = 0;
                    break;
                }
                else d = d - td;
            }
            printf("%d\n", cnt);
        }
    }
    return 0;
}