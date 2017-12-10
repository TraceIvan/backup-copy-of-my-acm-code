#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
struct P
{
    double x, y;
};
struct circle
{
    double x, y;
    double r;
};

int cmp(double x)
{
    if (fabs(x)<1e-15) return 0;
    if (x>0) return 1;
    return -1;
}

bool judge(double a, double b, double c, double &x1, double &x2)
{
    double tep = b*b - 4 * a*c;
    if (cmp(tep)<0) return 0;
    x1 = (-b + sqrt(tep)) / (2 * a);
    x2 = (-b - sqrt(tep)) / (2 * a);
    return 1;
}
bool judge(circle o, P a, P c)    //线段与圆的关系
{
    double k, b;
    if (cmp(a.x - c.x) == 0)
    {//如果为垂直于x轴的线段
        double t = o.r*o.r - (a.x - o.x)*(a.x - o.x);//半径的平方减去圆心到边的距离的平方
        if (t<0) return 0;//在圆外
        double maxy = max(a.y, c.y), miny = min(a.y, c.y), y1 = sqrt(t) + o.y, y2 = o.y - sqrt(t);
        if (cmp(miny - y1) <= 0 && cmp(y1 - maxy) <= 0) return 1;
        if (cmp(miny - y2) <= 0 && cmp(y2 - maxy) <= 0) return 1;
        return 0;
    }
    k = (a.y - c.y) / (a.x - c.x);//斜率
    b = a.y - k*a.x;//截距
    double x1, x2;
    int f = judge(k*k + 1, 2 * k*(b - o.y) - 2 * o.x, o.x*o.x + (b - o.y)*(b - o.y) - o.r*o.r, x1, x2);//方程联立得到系数a,b,c,x1,x2
    if (f == 0) return 0;//b^2-4ac小于0
    int maxx = max(a.x, c.x), minx = min(a.x, c.x);
    if (cmp(minx - x1) <= 0 && cmp(x1 - maxx) <= 0) return 1;//交点在线段上
    if (cmp(minx - x2) <= 0 && cmp(x2 - maxx) <= 0) return 1;
    return 0;
}
bool judge(circle o, P a, P b, P c)
{
    if (judge(o, a, b) || judge(o, a, c) || judge(o, b, c)) return 1;
    return 0;
}

int main()
{
    int t;
    circle o;
    P a, b, c;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%lf%lf%lf", &o.x, &o.y, &o.r);
        scanf("%lf%lf%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y);
        if (judge(o, a, b, c)) puts("Yes");
        else puts("No");
    }
    return 0;
}
