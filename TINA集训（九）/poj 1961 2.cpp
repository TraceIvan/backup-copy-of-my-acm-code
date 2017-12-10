#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<algorithm>
using namespace std;
#define N 1000010

char s[N];
int nextval[N];
int len;

void getnext(const char *s)
{
    int i = 0, j = -1;
    nextval[0] = -1;
    while (i != len)
    {
        if (j == -1 || s[i] == s[j])
            nextval[++i] = ++j;
        else
            j = nextval[j];
    }
}

int main()
{
    int T = 1;
    int length;
    while (scanf("%d", &len) && len)
    {
        scanf("%s", s);
        getnext(s);
        printf("Test case #%d\n", T++);
        for (int i = 1; i <= len; ++i)
        {
            length = i - nextval[i]; //循环节的长度
            if (i != length && i % length == 0) //如果有多个循环
                printf("%d %d\n", i, i / length);
        }
        printf("\n");
    }
    return 0;
}