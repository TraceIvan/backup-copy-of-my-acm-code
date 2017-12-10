#include<iostream>
#include<map>
using namespace std;
map<int, int>mp;
int main()
{
    int n, k;
    while (~scanf("%d", &n))
    {
        for (int i = 1; i <= n; i++)
        {
            int num;
            scanf("%d", &num);
            mp[num]++;
        }
        scanf("%d", &k);
        while (k--)
        {
            int num;
            scanf("%d", &num);
            printf("%d", mp[num]);
            if (k > 0) printf(" ");
        }
        printf("\n");
    }



    return 0;
}