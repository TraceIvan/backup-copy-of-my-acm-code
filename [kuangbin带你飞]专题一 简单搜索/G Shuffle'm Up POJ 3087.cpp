#include<iostream>
#include<memory.h>
using namespace std;
char s1[105];
char s2[105];
char des[210];
int main()
{
    int t;
    int Case = 1;
    scanf("%d", &t);
    while (t--)
    {
        int c;
        scanf("%d", &c);
        scanf("%s", s1);
        scanf("%s", s2);
        scanf("%s", des);
        int cnt = 0;
        char t1[105], t2[105],ts[210];
        memcpy(t1, s1, sizeof(s1));
        memcpy(t2, s2, sizeof(s2));
        while (1)
        {
            int len = 0;
            for (int i = 0; i < c; i++)
            {
                ts[len] = t2[i];
                len++;
                ts[len] = t1[i];
                len++;
            }
            cnt++;
            ts[len] = '\0';
            if (strcmp(ts,des)==0)
            {
                break;
            }
            for (int i = 0; i < c; i++) t1[i] = ts[i];
            for (int i = c; i < 2 * c; i++) t2[i-c] = ts[i];
            if (strcmp(t1,s1)==0 && strcmp(t2,s2)==0)
            {
                cnt = -1;
                break;
            }
        }
        printf("%d %d\n", Case, cnt);
        Case++;
    }


    return 0;
}