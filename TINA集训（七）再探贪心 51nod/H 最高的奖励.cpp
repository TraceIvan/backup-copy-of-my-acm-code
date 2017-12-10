#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;
const int maxn = 50010;
int num[maxn];
struct node
{
    int deadline;
    int v;
    friend bool operator<(const node& a,const node& b)
    {
        return a.deadline < b.deadline;
    }
}tasks[maxn];
struct Cmp
{
    bool operator()(int a,int b)
    {
        return a > b;
    }
};
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d%d", &tasks[i].deadline, &tasks[i].v);
        }
        sort(tasks, tasks + n);
        long long ans = 0;
        priority_queue<int, vector<int>, Cmp>q;
        for (int i = 0; i < n; i++)
        {
            if (tasks[i].deadline > q.size())
            {//如果当前完成任务的时间还有剩余
                q.push(tasks[i].v);
                ans += tasks[i].v;
            }
            else
            {//否则替换掉价值最低的
                if (tasks[i].v > q.top())
                {
                    ans += tasks[i].v - q.top();
                    q.pop();
                    q.push(tasks[i].v);
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}