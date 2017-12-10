#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
const int maxl = 300 * 300;
int numa[maxl];
int numb[maxl];
map<int, int>m;
void exchange(int x, vector<int>&v)
{
    vector<int>::iterator it;
    it = lower_bound(v.begin(), v.end(), x);
    int p = it - v.begin();
    v[p] = x;
}

int main()
{
    int t;
    int Case = 1;
    scanf("%d", &t);
    while (t--)
    {
        int n, p, q;
        scanf("%d%d%d", &n, &p, &q);
        for (int i = 0; i < p+1; i++)
        {
            scanf("%d", &numa[i]);
            m[numa[i]] = i + 1;
        }
        for (int i = 0; i < q+1; i++)
        {
            scanf("%d", &numb[i]);
            if (m[numb[i]]) numb[i] = m[numb[i]];
            else numb[i] = 0;
        }
        vector<int>minlen;
        minlen.push_back(numb[0]);
        for (int i = 1; i < q+1; i++)
        {
            if (numb[i] > minlen.back()) minlen.push_back(numb[i]);
            else
            {
                exchange(numb[i], minlen);
            }
        }
        printf("Case %d: %d\n",Case, minlen.size());
        Case++;
    }
    return 0;
}