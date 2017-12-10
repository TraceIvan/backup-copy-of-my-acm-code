#include<iostream>
#include<memory.h>
using namespace std;
int tp[200010];
int adm[200010];
int n, k, q;
int main()
{
    while (cin >> n >> k >> q)
    {
        memset(tp, 0, sizeof(tp));
        memset(adm, 0, sizeof(adm));
        int ml = 200000, mr =0;
        for (int i = 0; i < n; i++)
        {
            int l, r;
            cin >> l >> r;
            tp[l]++;
            tp[r + 1]--;
            if (l < ml) ml = l;
            if (r > mr) mr = r;
        }
        for (int i = ml; i <= mr; i++)
        {
            tp[i] = tp[i - 1] + tp[i];
            adm[i] = adm[i - 1];
            if (tp[i] >= k) adm[i]++;
        }
        for (int i = mr + 1; i <= 200000; i++) adm[i] = adm[mr];
        for (int i = 0; i < q; i++)
        {
            int l, r;
            cin >> l >> r;
            cout << adm[r] - adm[l - 1] << endl;
        }
    }
    return 0;
}