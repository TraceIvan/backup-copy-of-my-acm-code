#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
char s[12];
int main()
{
    while (~scanf("%s", s))
    {
        int len = strlen(s);
        sort(s, s + len);
        do
        {
            printf("%s\n", s);
        } while (next_permutation(s, s + len));
    }
    return 0;
}