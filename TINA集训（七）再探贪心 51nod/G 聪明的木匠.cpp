#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;
const int maxn = 50010;
int num[maxn];
struct Cmp
{ 
    bool operator()(int a, int b)
    {
        return a > b;
    }
};

int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        priority_queue<int, vector<int>, Cmp>q;
        long long sum = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &num[i]);
            q.push(num[i]);
        }
        while (q.size() >= 2)
        {
            int a = q.top();
            q.pop();
            int b = q.top();
            q.pop();
            sum += a + b;
            q.push(a + b);
        }
        printf("%lld\n", sum);
    }
    return 0;
}