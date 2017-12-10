#include<iostream>
#include<string.h>
using namespace std;
char s[110];
int main()
{
    while (~scanf("%s", s))
    {
        int ll = strlen(s);
        printf("%c%d%c\n", s[0], ll - 2, s[ll - 1]);
    }


    return 0;
}