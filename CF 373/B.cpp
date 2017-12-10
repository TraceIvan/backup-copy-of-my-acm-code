#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
char s[100010];
char a[100010];
char b[100010];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        scanf("%s", s);
        int totallen = strlen(s);
        int lena = (totallen + 1) / 2, lenb = totallen / 2;
        int cntar = 0, cntbr = 0;
        for (int i = 0; i < totallen; i++)
        {
            a[i/2] = s[i];
            if (s[i] == 'r')cntar++;
            i++;
            b[i/2] = s[i];
            if (s[i] == 'r')cntbr++;
        }
        if (lena == lenb)
        {
            int cnt = 0;
            if (cntar + cntbr == lena)cnt += min(cntar, cntbr);
            else if(cntar + cntbr > lena)cnt += min(lena - cntar, lena - cntbr) + (cntar + cntbr - lena);
            else cnt = min(cntar, cntbr) + lena - (cntar + cntbr);
            printf("%d\n", cnt);
        }
        else
        {
            int cnt = 0;
            if (cntar + cntbr == lena)
            {
                cnt = min(cntbr,cntar);
            }
            else if(cntar+cntbr>lena)
            {
                cnt = min(cntar, cntbr);
            }
            else 
            {
                cnt =min(lenb-cntbr,lena-cntar);
            }
            printf("%d\n", cnt);
        }
    }
    return 0;
}