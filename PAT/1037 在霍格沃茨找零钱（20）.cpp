#include<iostream>
using namespace std;
int main()
{
    int pg, ps, pk;
    int ag, as, ak;
    char c;
    while (~scanf("%d%c%d%c%d%d%c%d%c%d", &pg, &c, &ps, &c, &pk, &ag, &c, &as, &c, &ak))
    {
        long long p = pg * 17 * 29 + ps * 29 + ps;
        long long a = ag * 17 * 29 + as * 29 + as;
        int rg, rs, rk;
        if (a < p)
        {
            printf("-");
            if (pk >= ak) rk = pk - ak;
            else rk = pk + 29 - ak, ps--;
            if (ps >= as) rs = ps - as;
            else rs = ps + 17 - as, pg--;
            rg = pg - ag;
        }
        else
        {
            if (ak >= pk) rk = ak - pk;
            else rk = ak + 29 - pk, as--;
            if (as >= ps) rs = as - ps;
            else rs = as + 17 - ps, ag--;
            rg = ag - pg;
        }
        printf("%d.%d.%d\n", rg, rs, rk);
    }


    return 0;
}