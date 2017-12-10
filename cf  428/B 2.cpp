#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    int cnt = 0;
    for (int i = 1; i <= k; i++)
    {
        int num;
        scanf("%d", &num);
        cnt += (num+1) / 2;
    }
    if (cnt <= n * 4)printf("YES\n");
    else printf("NO\n");
    return 0;
}