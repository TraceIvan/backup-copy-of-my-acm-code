#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
int m,ans,len;
char s[5100];

void solve()
{
    for (int tlen = len; tlen >= 2; tlen--)
    {
        int bitlen = tlen / 2;
        int rear = 1;
        int sum = 0,dlen=0;
        for (int j=1;j<=bitlen;j++)
        {
            sum += abs(s[j] - s[tlen - j + 1]);
            if (sum<= m)
            {
                dlen++;
                ans = max(ans, dlen);
            }
            else
            {
                sum -= abs(s[rear] - s[tlen - rear + 1]);
                sum -= abs(s[j] - s[tlen - j + 1]);//等下次重新匹配
                j--;
                dlen--;
                rear++;
            }
        }
    }
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &m);
        scanf("%s", s + 1);
        len = strlen(s + 1);
        ans = 0;
        solve();
        reverse(s + 1, s + 1 + len);
        solve();
        printf("%d\n",ans);

    }
    return 0;
}

#include<bits/stdc++.h>
using namespace std;

const int maxn = 2e4 + 10;;
char str[maxn];
int m, len;
int solve()
{
    int ans = 0;
    for (int i = len; i >= 1; --i)//B子串的结尾处
    {
        int cnt = i / 2 - 1, d = 0, t = 0, p = 0;//cnt表示的是A子串的结尾处，d表示的是当前串的dis，t表示的是串的长度
        for (int j = 0; j <= cnt; ++j)//j表示的是A串的开始坐标
        {
            d += abs(str[1 + j] - str[i - j]);///串的长度往后扩展
            if (d > m)//这里表示的是当前串的dis超过限制，将串从前面减少，然后从后面增加
            {
                d -= abs(str[1 + p] - str[i - p]);
                d -= abs(str[1 + j] - str[i - j]);
                p++;//前面减去的串的长度
                t--;//串的长度也要变化
                j--;
            }
            else
            {
                t++;
                ans = max(ans, t);
            }
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
    {
        int ans = 0;
        cin >> m >> str + 1;//从第一位开始赋值
        len = strlen(str + 1);
        ans = max(ans, solve());//正序的这次是拿后面的那一部分来与前面的那一部分进行匹配
        reverse(str + 1, str + len + 1);
        ans = max(ans, solve());//反序的正好反过来，是用原序列里面前面的那一部分来匹配后面的那一部分
        cout << ans << endl;
    }
    return 0;
}