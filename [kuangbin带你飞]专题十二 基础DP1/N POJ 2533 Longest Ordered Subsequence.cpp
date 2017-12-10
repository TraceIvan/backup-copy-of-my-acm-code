#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn = 1010;
int num[maxn];
int pre[maxn];
int dp[maxn];
int n;
int DPn2()
{
    memset(pre, -1, sizeof(pre));
    dp[0] = 1;
    int ans = 1;
    for (int i = 1; i < n; i++)
    {
        dp[i] = 1;
        for (int j = i - 1; j >= 0; j--)
        {
            if (num[i] > num[j] && dp[j] + 1 > dp[i])
            {
                dp[i] = dp[j] + 1;
                pre[i] = j;
            }
        }
        if (dp[i] > ans) ans = dp[i];
    }
    return ans;
}
int Vnlogn()
{
    vector<int>v;
    for (int i = 0; i < n; i++)
    {
        if (v.empty()) v.push_back(num[i]);
        else if (num[i] > v.back()) v.push_back(num[i]);
        else
        {
            int pos = lower_bound(v.begin(), v.end(), num[i]) - v.begin();
            v[pos] = num[i];
        }
    }
    return v.size();
}
int main()
{
    while (~scanf("%d", &n))
    {
        for (int i = 0; i < n; i++) scanf("%d", &num[i]);
        printf("%d\n", DPn2());
        //printf("%d\n", Vnlogn());
    }
    return 0;
}