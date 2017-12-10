#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
int n;
const int maxn = 10010;
struct node
{
    int x;
    int y;
}ll[maxn];
bool Cmp(const node&a, const node&b)
{
    if (a.x == b.x)return a.y < b.y;
    else return a.x < b.x;
}
struct Cmp1
{
    bool operator() (int a, int b)
    {
        return a > b;
    }
};

int main()
{
    while (~scanf("%d", &n))
    {
        for (int i = 0; i < n; i++) scanf("%d%d", &ll[i].x, &ll[i].y);
        sort(ll, ll + n, Cmp);

        priority_queue<int,vector<int>,Cmp1>q;
        q.push(ll[0].y);
        int ans = 1;
        for (int i = 1; i < n; i++)
        {
            int t = q.top();
            if (ll[i].x >= t)
            {
                q.pop();
                q.push(ll[i].y);
            }
            else
            {
                ans++;
                q.push(ll[i].y);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}