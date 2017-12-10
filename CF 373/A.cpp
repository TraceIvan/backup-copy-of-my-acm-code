#include<iostream>
using namespace std;
int num[100];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        for (int i = 0; i < n; i++) scanf("%d", &num[i]);
        if (n == 1&&num[n-1]!=15&&num[n-1]!=0)printf("-1\n");
        else if (num[n - 1] > num[n - 2] && num[n - 1] != 15||(num[n-1]==0&&num[n-2]==1)||(n==1&&num[n-1]==0)) printf("UP\n");
        else printf("DOWN\n");
    }
    return 0;
}