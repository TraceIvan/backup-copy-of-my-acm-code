#include<iostream>
#include<vector>
#include<memory.h>
#include<algorithm>
using namespace std;
const int maxn = 10005;
int maxl[maxn];
int maxr[maxn];
int p[maxn];
void exchange(int x, int pos, vector<int>&v, char c)
{
    vector<int>::iterator it;
    it = lower_bound(v.begin(), v.end(), x);
    int p = it - v.begin();
    v[p] = x;
    if (c == 'l')maxl[pos] = p;
    else maxr[pos] = p;
}
int main()
{
    int n;
    while (cin >> n)
    {
        vector<int>minlen;
        for (int i = 0; i < n; i++) cin >> p[i];
        minlen.push_back(p[0]);
        maxl[0] = 0;
        for (int i = 1; i < n; i++)
        {
            if (p[i] > minlen.back())
            {
                maxl[i] = minlen.size();
                minlen.push_back(p[i]);
            }
            else
            {
                exchange(p[i], i, minlen, 'l');
            }
        }
        minlen.clear();
        minlen.push_back(p[n - 1]);
        maxr[n - 1] = 0;
        for (int i = n - 2; i >= 0; i--)
        {
            if (p[i] > minlen.back())
            {
                maxr[i] = minlen.size();
                minlen.push_back(p[i]);
            }
            else
            {
                exchange(p[i], i, minlen, 'r');
            }
        }
        int len = 0;
        for (int i = 0; i < n; i++)
        {
            int tmp = min(maxl[i], maxr[i]) * 2 + 1;
            if (tmp > len) len = tmp;
        }
        cout << len << endl;
    }
    return 0;
}
