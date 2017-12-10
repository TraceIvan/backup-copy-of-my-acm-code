#include<iostream>
#include<memory.h>
#include<set>
#include<algorithm>
using namespace std;
int num[50020];
int main()
{
    int n,k;
    while (~scanf("%d%d",&k, &n))
    {
        set<int>s;
        for (int i = 0; i < n; i++)
        {
            cin >> num[i];
            s.insert(num[i]);
        }
        sort(num, num + n);
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            int t = k - num[i];
            if (t <= num[i])break;
            if (s.count(t))
            {
                printf("%d %d\n", num[i], t);
                cnt++;
            }
        }
        if (cnt == 0) printf("No Solution\n");
    }

    return 0;
}