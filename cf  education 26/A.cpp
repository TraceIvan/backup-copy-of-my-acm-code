#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n;
const int maxn = 250;
char s[maxn];
int main()
{
    while (~scanf("%d", &n))
    {
        cin.get();
        gets_s(s,maxn);
        int ans = 0;
        for (int i = 0; i < n;)
        {
            while (i<n&&s[i] == ' ')i++;
            int tv = 0;
            while (i < n&&s[i] != ' ')
            {
                if (s[i] >= 'A'&&s[i] <= 'Z') tv++;
                i++;
            }
            ans = max(ans, tv);
        }
        printf("%d\n", ans);
    }


    return 0;
}