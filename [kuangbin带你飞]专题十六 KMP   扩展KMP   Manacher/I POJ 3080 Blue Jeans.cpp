#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

const int N = 107;
char s[N][61];
int Next[N];

void GetNext(char a[], int n)
{
    int i = 0, j = -1;
    Next[0] = -1;
    while (i<n)
    {
        if (j == -1 || a[i] == a[j])
            Next[++i] = ++j;
        else
            j = Next[j];
    }
}

int kmp(char a[], char b[], int n)
{
    int i = 0, j = 0;
    while (i<60)
    {

        if (j == -1 || b[i] == a[j])
            i++, j++;
        else
            j = Next[j];
        if (j == n)
            return true;
    }
    return false;
}

int main()
{
    int T, n, f;
    scanf("%d", &T);
    while (T--)
    {
        char ans[N] = "Z";
        scanf("%d", &n);
        for (int i = 0; i<n; i++)
            scanf("%s", s[i]);
        for (int len = 60; len >= 3; len--)//子串的长度
        {
            for (int i = 0; i <= 60 - len; i++)//子串的开始下标
            {
                char subStr[N] = { 0 };
                strncpy(subStr, s[0] + i, len);

                GetNext(subStr, len);//从subStr中得到Next
                int flag = 0;
                for (int j = 1; j<n; j++)
                {
                    if (!kmp(subStr, s[j], len))
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0 && strcmp(ans, subStr)>0)
                    strcpy(ans, subStr);
            }
            f = 0;
            if (ans[0] != 'Z')
            {
                printf("%s\n", ans);
                f = 1;
                break;
            }
        }
        if (f == 0)
            printf("no significant commonalities\n");

    }
    return 0;
}