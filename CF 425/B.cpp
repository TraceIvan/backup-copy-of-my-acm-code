#include<iostream>
#include<memory.h>
#include<string.h>
using namespace std;
bool good[26];
char gd[30];
char p[100010];
char s[100010];
int main()
{
    while (~scanf("%s", gd))
    {
        memset(good, 0, sizeof(good));
        for (int i = 0; gd[i] != '\0'; i++) good[gd[i] - 'a'] = true;
        scanf("%s", p);
        int lenp = strlen(p);
        int q;
        scanf("%d", &q);
        for (int i = 0; i < q; i++)
        {
            scanf("%s", s);
            int len = strlen(s);
            int d = len - lenp;
            if (d < 0)
            {
                if (d<-1) printf("NO\n");
                else
                {
                    bool flag = true;
                    for (int i = 0,j=0; i < lenp; j++,i++)
                    {
                        if (p[i] == '*') j--;
                        else
                        {
                            if (p[i] == s[j]) continue;
                            else
                            {
                                if (p[i] == '?'&&good[s[j] - 'a']) continue;
                                else
                                {
                                    flag = false;
                                    break;
                                }
                            }
                        }
                    }
                    if (flag) printf("YES\n");
                    else printf("NO\n");
                }
            }
            else
            {
                d = d + 1;
                bool flag = true;
                int j,i;
                for (i = 0,j=0; i < lenp; i++,j++)
                {
                    if (p[i] == s[j]) continue;
                    else if (p[i] == '?')
                    {
                        if (!good[s[j] - 'a'])
                        {
                            flag = false;
                            break;
                        }
                    }
                    else if(p[i]=='*')
                    {
                        for (int k = 0; k < d; k++)
                        {
                            if (good[s[j + k]-'a'])
                            {
                                flag = false;
                                break;
                            }
                        }
                        if (!flag) break;
                        j += d-1;
                    }
                    else
                    {
                        flag = false;
                        break;
                    }
                }
                if (j < len) flag = false;
                if (flag) printf("YES\n");
                else printf("NO\n");
            }
        }
    }
    return 0;
}