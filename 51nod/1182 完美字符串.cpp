#include<iostream>
#include<memory.h>
#include<string.h>
#include<cctype>
#include<algorithm>
using namespace std;
int num[26];
char s[10010];
int main()
{
    while (~scanf("%s", s))
    {
        memset(num, 0, sizeof(num));
        int len = strlen(s);
        for (int i = 0; i < len; i++)
        {
            num[tolower(s[i]) - 'a']++;
        }
        sort(num, num + 26);
        int sum = 0;
        for (int i = 1; i <= 26; i++) sum += i*num[i - 1];
        printf("%d\n", sum);
    }
    return 0;
}