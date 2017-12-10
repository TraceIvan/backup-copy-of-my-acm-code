#include<iostream>
#include<memory.h>
#include<string.h>
#include<algorithm>
using namespace std;
int n;
const int maxlen = 100010;
const int MOD = (int)1e9 + 7;
int maxll;
struct node
{
    char c;
    char s[maxlen];
}words[26];
bool vis[26];//记录哪个字符在首位出现过
char str[maxlen];//记录读入的字符串
int val[26];//分配0~25
bool Cmp(const node&a, const node&b)
{
    for (int i =maxll; i > 0; --i)
    {
        if (a.s[i] != b.s[i])return a.s[i] < b.s[i];
    }
    return a.s[0] < b.s[0];
}
int main()
{
    int Case = 1;
    while (~scanf("%d", &n))
    {
        //初始化
        maxll = 0;
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < 26; i++)
        {
            words[i].c = 'a' + i;
            memset(words[i].s,'\0', sizeof(char)*maxlen);
        }
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
        {
            scanf("%s", str);
            int len = strlen(str);
            if (len > 1) vis[str[0] - 'a'] = true;
            int x, y;
            for (int j = len - 1; j >= 0; --j)
            {
                x = str[j] - 'a';
                y = len - 1 - j;
                words[x].s[y]++;
                while (words[x].s[y] == 26)
                {
                    words[x].s[y] = 0;
                    words[x].s[y + 1]++;
                    y++;
                }
            }
            maxll = max(maxll, y);
        }
        maxll += 5;
        sort(words, words + 26, Cmp);
        //找第一个没在首位的字符
        int pos = 0;
        for (int i = 0; i < 26; i++)
        {
            if (!vis[words[i].c-'a'])
            {
                pos = i;
                break;
            }
        }
        for (int i = 0; i < 26; i++)
        {
            if (i< pos) val[i] = i + 1;
            else if (i == pos) val[i] = 0;
            else val[i] = i;
        }
        long long sum = 0;
        for (int i = 0; i < 26; i++)
        {
            long long temp = 0;
            long long Base = 1;
            for (int j = 0; j <maxll; j++)
            {
                temp = (temp+(words[i].s[j] -'\0')*Base% MOD)%MOD;
                Base = (Base * 26) % MOD;
            }
            sum = (sum+temp*val[i] % MOD)% MOD;
        }
        printf("Case #%d: %lld\n",Case++, sum);
    }
    return 0;
}