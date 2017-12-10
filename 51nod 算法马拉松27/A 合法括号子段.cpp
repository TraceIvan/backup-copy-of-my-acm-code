#include<iostream>
#include<stack>
#include<string.h>
#include<cstdio>
using namespace std;
const int maxn = 1100010;
char ini[maxn];
int num[maxn];
//()()(())
//1 1 2  1+3*4/2
//()(())()(()((
//1 2  1 01 00 3*4/2+1+1 
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        memset(num, 0, sizeof(num));
        scanf("%s", ini);
        int len = strlen(ini);
        stack<int>s;
        int cntl = 0;//¼ÇÂ¼')'
        int cntr = 0;
        int pos = 0;
        for (; pos < len&&ini[pos] == ')'; pos++)num[cntr++]=0;
        while ( pos < len)
        {
            if (ini[pos] == '(')
            {
                s.push(++cntl);
                pos++;
            }
            else
            {
                int count = 0,ps;
                while (pos<len&&!s.empty()&&ini[pos]==')')
                {
                    num[cntr++] = s.top();
                    s.pop();
                    pos++;
                }
                while (pos < len&&ini[pos] == ')')
                {
                    num[cntr++] = 0;
                    pos++;
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < cntr;)
        {
            if (num[i] == 0)
            {
                i++;
                continue;
            }
            else
            {
                int cnt = 1;
                if (i + 1 < cntr&&num[i + 1] == num[i] + 1)
                {
                    while (i + 1 < cntr&&num[i + 1] == num[i] + 1)
                    {
                        cnt++;
                        i++;
                    }
                    ans += cnt*(cnt + 1) / 2;
                }
                else
                {
                    while (i + 1 < cntr&&num[i+1]!=0&&num[i + 1] == num[i] - 1)
                    {
                        cnt++;
                        i++;
                    }
                    ans += cnt;
                }
                i++;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}