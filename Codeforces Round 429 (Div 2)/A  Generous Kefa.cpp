#include<iostream>
#include<map>
#include<string>
#include<cstring>
using namespace std;
map<char, int>mp;
char s[110];
int main()
{
    int n, k;
    while (~scanf("%d%d", &n, &k))
    {
        mp.clear();
        scanf("%s", s);
        int max = 0;
        int len = strlen(s);
        for (int i = 0; i < len; i++)
        {
            mp[s[i]]++;
            if (mp[s[i]] > max) max = mp[s[i]];
        }
        if (max <= k) printf("YES\n");
        else printf("NO\n");
        
    }
    return 0;
}