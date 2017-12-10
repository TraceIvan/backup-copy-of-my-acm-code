#include<iostream>
using namespace std;
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        int cnte = 0, cnt4 = 0, cnt2 = 0;
        for (int i = 1; i <= n; i++)
        {
            int num;
            scanf("%d", &num);
            if (num % 2) cnte++;
            else if (num % 4) cnt2++;
            else cnt4++;
        }
        if (cnt2 == 0)
        {
            if (cnt4 >= cnte - 1)printf("Yes\n");
            else printf("No\n");
        }
        else if(cnt4>=cnte)printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}