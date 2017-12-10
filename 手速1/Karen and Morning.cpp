#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
    int hh, mm;
    char c;
    while (cin >> hh >> c >> mm)
    {
        int nhh = hh % 10 * 10 + hh / 10;
        int t = 0;
        if (nhh == mm)
        {
            printf("%d\n",t);
        }
        else
        {
            int dhh = hh, dmm = mm;
            while (1)
            {
                dmm++;
                t++;
                if (dmm == 60)
                {
                    dmm = 0;
                    dhh = (dhh + 1) % 24;
                }
                int ndhh = dhh % 10 * 10 + dhh / 10;
                if (ndhh == dmm)
                {
                    printf("%d\n",t);
                    break;
                }
            }
        }
    }
    return 0;
}