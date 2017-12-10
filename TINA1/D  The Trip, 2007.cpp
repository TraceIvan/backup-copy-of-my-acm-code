//题意：求最小的大包数目，同时使每个大包的里小包的数目最小
//显然，相同大小的包只能放在不同的大包里，那么最小的大包数目就是相同大小的包的最大数目。之后，每个大包里的小包。
#include<iostream>
#include<algorithm>
using namespace std;
int dm[10005];
int main()
{
    int k = 1,n;
    while (cin >> n, n != 0)
    {
        for (int i = 0; i < n; i++) cin >> dm[i];
        sort(dm, dm + n);
        int maxt = 1;
        for (int i = 1, t = 1; i < n; i++)
        {
            if (dm[i] == dm[i - 1]) t++;
            else
            {
                if (t > maxt) maxt = t;
                t = 1;
            }
        }
        if (t > maxt) maxt = t;
        if (k > 1) cout << endl;
        cout << maxt << endl;
        for (int i = 0; i < maxt; i++)
        {
            for (int j = i; j < n; j += maxt)
            {
                if (j == i) cout << dm[j];
                else cout << ' ' << dm[j];
            }
            cout << endl;
        }
        k++;
    }
    return 0;
}