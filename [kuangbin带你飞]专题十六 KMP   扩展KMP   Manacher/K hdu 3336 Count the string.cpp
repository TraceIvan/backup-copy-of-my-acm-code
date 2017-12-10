#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 100017;

char strm[MAXN];//密码表
char strz[MAXN];//不完整的密文和密文
char str[MAXN]; //密码表转换后
char s[MAXN];   //密文和明文转换后
int Next[MAXN];

void getnext(char T[], int len)
{
    int i = 0, j = -1;
    Next[0] = -1;
    while (i < len)
    {
        if (j == -1 || T[i] == T[j])
        {
            i++, j++;
            Next[i] = j;
        }
        else
            j = Next[j];
    }
}
int KMP(int len1, int len2)
{
    int i, j = 0;
    if (len1 % 2 == 1)
    {
        i = len1 / 2 + 1;
    }
    else
        i = len1 / 2;
    while (i < len1 && j < len2)
    {
        if (j == -1 || strz[i] == s[j])
        {
            i++, j++;
        }
        else
            j = Next[j];
    }
    return j;//j值代表的就是前缀和后缀的最长相等长度
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%s", strm);
        for (int i = 0; i < 26; i++)
        {
            char ss = strm[i];
            str[ss] = i;
        }
        scanf("%s", strz);
        int lenz = strlen(strz);
        for (int i = 0; i < lenz; i++)//将密文和明文按照密码表转换
        {
            int tt = str[strz[i]];
            s[i] = 'a' + tt;
        }
        int lens = strlen(s);
        getnext(s, lens);
        int j = KMP(lenz, lens);//得到密文的个数
        if (j * 2 == lenz)//前缀和后缀恰各占一半
        {
            printf("%s\n", strz);
        }
        else
        {
            int tt = lenz - j;
            printf("%s", strz);
            for (int i = j; i < tt; i++)//需要添加的明文
            {
                printf("%c", s[i]);
            }
            printf("\n");
        }
    }
    return 0;
}
