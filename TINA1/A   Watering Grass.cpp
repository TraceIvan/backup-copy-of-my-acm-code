#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
struct sprk
{
    double r,ldis;
    double L, R;
}v[10005];
double n, l, w;
bool Cmp(const sprk& a, const sprk& b)
{
    if (a.L < b.L) return true;
    else if (a.L == b.L)
    {
        if (a.R < b.R) return true;
        else return false;
    }
    else return false;
}
int main()
{
    while (cin >> n >> l >> w)
    {
        int sz = 0;
        sprk tmp;
        for (int i = 0; i < n; i++)
        {
            cin >> tmp.ldis >> tmp.r;
            if (tmp.r <=w/2.0) continue;
            double tl = sqrt(tmp.r*tmp.r-w*w/4.0);
            tmp.L = tmp.ldis*1.0 - tl;
            tmp.R = tmp.ldis*1.0 + tl;
            if (tmp.R < 0) continue;
            v[sz++] = tmp;
        }
        sort(v, v+sz, Cmp);
        int num = 0;
        double pos = 0;
        int k = 0;
        bool ok = false;
        if (sz>0&&v[0].L <= 0)
        {
            k = 0;
            pos = 0;
            while (k < sz)
            {
                int j = k;
                double Rpos = pos;
                while (j < sz&&v[j].L <= pos)
                {
                    if (v[j].R > Rpos) Rpos = v[j].R;
                    ++j;
                }
                if (j == k)break;
                num++;
                pos = Rpos;
                k = j;
                if (pos >= l)
                {
                    ok = true;
                    break;
                }
            }
        }
        if(ok) cout << num << endl;
        else cout << -1 << endl;
    }
    return 0;
}