#include<iostream>
using namespace std;
int num[1000010];
int main()
{
    int odd = 0, even = 0;
    long long sum = 0;
    int n;
    while (~scanf("%d", &n))
    {
        sum = 0, odd = 0, even = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &num[i]);
            sum += num[i];
            if (num[i] % 2) odd++;
            else even++;
        }
        if (odd==0) printf("Second\n");
        else printf("First\n");
    }
    return 0;
}