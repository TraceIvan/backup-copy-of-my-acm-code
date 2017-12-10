#include<iostream>
using namespace std;
int num[110];
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    int sum = 0;
    int remain = 0;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (num[i] >= 8)
        {
            sum += 8;
            remain += num[i] - 8;
        }
        else
        {
            if (remain + num[i] >= 8)
            {
                remain = remain + num[i] - 8;
                sum += 8;
            }
            else
            {
                sum += remain+num[i];
                remain = 0;
            }
        }
        cnt++;
        if (sum >= k)break;
    }
    if(sum>=k)printf("%d\n", cnt);
    else printf("-1\n");
    return 0;
}