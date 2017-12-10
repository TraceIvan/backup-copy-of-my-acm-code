#include<iostream>
#include<string.h>
using namespace std;
char num[200100];
char num2[200100];
int main()
{
    int n, t;
    while (~scanf("%d%d", &n, &t))
    {
        scanf("%s", num+1);
        int len = strlen(num+1);
        char *pos = strchr(num+1, '.');
        if (pos == NULL)printf("%s\n", num+1);
        else
        {
            char *tp = pos+1;
            while (*tp != '\0'&&*tp < '5')tp++;
            if (*tp == '\0') printf("%s\n", num+1);
            else
            {
                while (t--)
                {
                    *tp = '\0';
                    tp--;
                    if (*tp != '.')
                    {
                        if (*tp + 1 <= '9') *tp = *tp + 1;
                        else
                        {
                            while (*tp != '.'&&*tp + 1 > '9')
                            {
                                *tp = '\0';
                                tp--;
                            }
                            if (*tp != '.')*tp = *tp + 1;
                            else goto BEFORE;
                        }
                        if (*tp< '5')break;
                    }
                    else
                    {
                    BEFORE:
                        *tp = '\0';
                        tp--;
                        if (*tp + 1 <= '9')*tp = *tp + 1;
                        else
                        {
                            while (*tp + 1 > '9')
                            {
                                *tp = '0';
                                tp--;
                            }
                            if (tp >= &num[1]) *tp = *tp + 1;
                            else *tp = '1';
                        }
                        break;
                    }
                }
                if (tp >= &num[1]) printf("%s\n", num + 1);
                else printf("%s\n", num);
            }
        }
    }
    return 0;
}