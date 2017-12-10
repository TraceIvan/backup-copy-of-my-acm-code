#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
int main()
{
    int t;
    scanf("%d", &t);
    char a[80010], b[80010];
    while (t--)
    {
        int n, x, y;
        scanf("%d%d%d", &n, &x, &y);
        scanf("%s", a);
        scanf("%s", b);
        int same = 0;
        for (int i = 0; i < n; i++) if (a[i] == b[i]) same++;
        int tx = 0, ty = 0;
        tx = ty = min(same, min(x, y));
        int dx = x - tx, dy = y - ty;
        if (dx + dy <= n - same)printf("Not lying\n");
        else printf("Lying\n");
    }
    return 0;
}