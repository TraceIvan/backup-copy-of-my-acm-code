#include<iostream>
#include<algorithm>
using namespace std;
int n,a,b;
struct node
{
    int x;
    int y;
}points[110];
bool Judge(int i, int j)
{
    int x1 = points[i].x, y1 = points[i].y;
    int x2 = points[j].x, y2 = points[j].y;
    if (x1 + x2 <= a)
    {
        if (max(y1, y2) <= b)return true;
    }
    if (x1 + y2 <= a)
    {
        if (max(y1, x2) <= b)return true;
    }
    if (y1 + x2 <= a)
    {
        if (max(x1,y2) <= b) return true;
    }
    if (y1 + y2 <= a)
    {
        if (max(x1, x2) <= b)return true;
    }
    if (x1 + x2 <= b)
    {
        if (max(y1, y2) <= a)return true;
    }
    if (x1 + y2 <= b)
    {
        if (max(y1, x2) <= a)return true;
    }
    if (y1 + x2 <= b)
    {
        if (max(x1, y2) <= a) return true;
    }
    if (y1 + y2 <= b)
    {
        if (max(x1, x2) <= a)return true;
    }
    return false;
}
int main()
{
    while (~scanf("%d%d%d", &n, &a, &b))
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d%d", &points[i].x, &points[i].y);
        }
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (Judge(i, j))
                {
                    ans = max(ans, points[i].x*points[i].y + points[j].x*points[j].y);
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}