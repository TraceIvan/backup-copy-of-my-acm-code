#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
using namespace std;
const int MOD = 10007;
const int MAXN = 100010;
struct Node
{
    int l, r;
    int sum1, sum2, sum3;//维护和、平方和、三次方和
    int lazy1, lazy2, lazy3;//+、*、=
}segTree[MAXN * 3];
void build(int i, int l, int r)
{
    segTree[i].l = l;
    segTree[i].r = r;
    segTree[i].sum1 = segTree[i].sum2 = segTree[i].sum3 = 0;
    segTree[i].lazy1 = segTree[i].lazy3 = 0;
    segTree[i].lazy2 = 1;
    int mid = (l + r) / 2;
    if (l == r)return;
    build(i << 1, l, mid);
    build((i << 1) | 1, mid + 1, r);
}
void push_up(int i)
{
    if (segTree[i].l == segTree[i].r)
        return;
    segTree[i].sum1 = (segTree[i << 1].sum1 + segTree[(i << 1) | 1].sum1) % MOD;
    segTree[i].sum2 = (segTree[i << 1].sum2 + segTree[(i << 1) | 1].sum2) % MOD;
    segTree[i].sum3 = (segTree[i << 1].sum3 + segTree[(i << 1) | 1].sum3) % MOD;

}

void push_down(int i)
{
    if (segTree[i].l == segTree[i].r) return;
    if (segTree[i].lazy3 != 0)//直接赋值操作
    {
        segTree[i << 1].lazy3 = segTree[(i << 1) | 1].lazy3 = segTree[i].lazy3;
        segTree[i << 1].lazy1 = segTree[(i << 1) | 1].lazy1 = 0;//初始化+、*标记
        segTree[i << 1].lazy2 = segTree[(i << 1) | 1].lazy2 = 1;
        segTree[i << 1].sum1 = (segTree[i << 1].r - segTree[i << 1].l + 1)*segTree[i << 1].lazy3%MOD;
        segTree[i << 1].sum2 = (segTree[i << 1].r - segTree[i << 1].l + 1)*segTree[i << 1].lazy3%MOD*segTree[i << 1].lazy3%MOD;
        segTree[i << 1].sum3 = (segTree[i << 1].r - segTree[i << 1].l + 1)*segTree[i << 1].lazy3%MOD*segTree[i << 1].lazy3%MOD*segTree[i << 1].lazy3%MOD;
        segTree[(i << 1) | 1].sum1 = (segTree[(i << 1) | 1].r - segTree[(i << 1) | 1].l + 1)*segTree[(i << 1) | 1].lazy3%MOD;
        segTree[(i << 1) | 1].sum2 = (segTree[(i << 1) | 1].r - segTree[(i << 1) | 1].l + 1)*segTree[(i << 1) | 1].lazy3%MOD*segTree[(i << 1) | 1].lazy3%MOD;
        segTree[(i << 1) | 1].sum3 = (segTree[(i << 1) | 1].r - segTree[(i << 1) | 1].l + 1)*segTree[(i << 1) | 1].lazy3%MOD*segTree[(i << 1) | 1].lazy3%MOD*segTree[(i << 1) | 1].lazy3%MOD;
        segTree[i].lazy3 = 0;
    }
    if (segTree[i].lazy1 != 0 || segTree[i].lazy2 != 1)
    {//如果存在+、*标记
        segTree[i << 1].lazy1 = (segTree[i].lazy2*segTree[i << 1].lazy1%MOD + segTree[i].lazy1) % MOD;
        segTree[i << 1].lazy2 = segTree[i << 1].lazy2*segTree[i].lazy2%MOD;
        int sum1, sum2, sum3;
        sum1 = (segTree[i << 1].sum1*segTree[i].lazy2%MOD + (segTree[i << 1].r - segTree[i << 1].l + 1)*segTree[i].lazy1%MOD) % MOD;
        sum2 = (segTree[i].lazy2 * segTree[i].lazy2 % MOD * segTree[i << 1].sum2 % MOD + 2 * segTree[i].lazy1*segTree[i].lazy2%MOD * segTree[i << 1].sum1%MOD + (segTree[i << 1].r - segTree[i << 1].l + 1)*segTree[i].lazy1%MOD*segTree[i].lazy1%MOD) % MOD;
        sum3 = segTree[i].lazy2 * segTree[i].lazy2 % MOD * segTree[i].lazy2 % MOD * segTree[i << 1].sum3 % MOD;
        sum3 = (sum3 + 3 * segTree[i].lazy2 % MOD * segTree[i].lazy2 % MOD * segTree[i].lazy1 % MOD * segTree[i << 1].sum2) % MOD;
        sum3 = (sum3 + 3 * segTree[i].lazy2 % MOD * segTree[i].lazy1 % MOD * segTree[i].lazy1 % MOD * segTree[i << 1].sum1) % MOD;
        sum3 = (sum3 + (segTree[i << 1].r - segTree[i << 1].l + 1)*segTree[i].lazy1%MOD * segTree[i].lazy1 % MOD * segTree[i].lazy1 % MOD) % MOD;
        segTree[i << 1].sum1 = sum1;
        segTree[i << 1].sum2 = sum2;
        segTree[i << 1].sum3 = sum3;
        segTree[(i << 1) | 1].lazy1 = (segTree[i].lazy2*segTree[(i << 1) | 1].lazy1%MOD + segTree[i].lazy1) % MOD;
        segTree[(i << 1) | 1].lazy2 = segTree[(i << 1) | 1].lazy2 * segTree[i].lazy2 % MOD;
        sum1 = (segTree[(i << 1) | 1].sum1*segTree[i].lazy2%MOD + (segTree[(i << 1) | 1].r - segTree[(i << 1) | 1].l + 1)*segTree[i].lazy1%MOD) % MOD;
        sum2 = (segTree[i].lazy2 * segTree[i].lazy2 % MOD * segTree[(i << 1) | 1].sum2 % MOD + 2 * segTree[i].lazy1*segTree[i].lazy2%MOD * segTree[(i << 1) | 1].sum1%MOD + (segTree[(i << 1) | 1].r - segTree[(i << 1) | 1].l + 1)*segTree[i].lazy1%MOD*segTree[i].lazy1%MOD) % MOD;
        sum3 = segTree[i].lazy2 * segTree[i].lazy2 % MOD * segTree[i].lazy2 % MOD * segTree[(i << 1) | 1].sum3 % MOD;
        sum3 = (sum3 + 3 * segTree[i].lazy2 % MOD * segTree[i].lazy2 % MOD * segTree[i].lazy1 % MOD * segTree[(i << 1) | 1].sum2) % MOD;
        sum3 = (sum3 + 3 * segTree[i].lazy2 % MOD * segTree[i].lazy1 % MOD * segTree[i].lazy1 % MOD * segTree[(i << 1) | 1].sum1) % MOD;
        sum3 = (sum3 + (segTree[(i << 1) | 1].r - segTree[(i << 1) | 1].l + 1)*segTree[i].lazy1%MOD * segTree[i].lazy1 % MOD * segTree[i].lazy1 % MOD) % MOD;
        segTree[(i << 1) | 1].sum1 = sum1;
        segTree[(i << 1) | 1].sum2 = sum2;
        segTree[(i << 1) | 1].sum3 = sum3;
        segTree[i].lazy1 = 0;
        segTree[i].lazy2 = 1;

    }
}
void update(int i, int l, int r, int type, int c)
{
    if (segTree[i].l == l && segTree[i].r == r)
    {
        c %= MOD;
        if (type == 1)
        {
            segTree[i].lazy1 += c;
            segTree[i].lazy1 %= MOD;
            segTree[i].sum3 = (segTree[i].sum3 + 3 * segTree[i].sum2%MOD*c%MOD + 3 * segTree[i].sum1%MOD*c%MOD*c%MOD + (segTree[i].r - segTree[i].l + 1)*c%MOD*c%MOD*c%MOD) % MOD;
            segTree[i].sum2 = (segTree[i].sum2 + 2 * segTree[i].sum1%MOD*c%MOD + (segTree[i].r - segTree[i].l + 1)*c%MOD*c%MOD) % MOD;
            segTree[i].sum1 = (segTree[i].sum1 + (segTree[i].r - segTree[i].l + 1)*c%MOD) % MOD;
        }
        else if (type == 2)
        {
            segTree[i].lazy1 = segTree[i].lazy1*c%MOD;
            segTree[i].lazy2 = segTree[i].lazy2*c%MOD;
            segTree[i].sum1 = segTree[i].sum1*c%MOD;
            segTree[i].sum2 = segTree[i].sum2*c%MOD*c%MOD;
            segTree[i].sum3 = segTree[i].sum3*c%MOD*c%MOD*c%MOD;
        }
        else
        {
            segTree[i].lazy1 = 0;
            segTree[i].lazy2 = 1;
            segTree[i].lazy3 = c%MOD;
            segTree[i].sum1 = c*(segTree[i].r - segTree[i].l + 1) % MOD;
            segTree[i].sum2 = c*(segTree[i].r - segTree[i].l + 1) % MOD*c%MOD;
            segTree[i].sum3 = c*(segTree[i].r - segTree[i].l + 1) % MOD*c%MOD*c%MOD;
        }
        return;
    }
    push_down(i);
    int mid = (segTree[i].l + segTree[i].r) / 2;
    if (r <= mid)update(i << 1, l, r, type, c);
    else if (l > mid)update((i << 1) | 1, l, r, type, c);
    else
    {
        update(i << 1, l, mid, type, c);
        update((i << 1) | 1, mid + 1, r, type, c);
    }
    push_up(i);
}
int query(int i, int l, int r, int p)
{
    if (segTree[i].l == l && segTree[i].r == r)
    {
        if (p == 1)return segTree[i].sum1;
        else if (p == 2)return segTree[i].sum2;
        else return segTree[i].sum3;
    }
    push_down(i);
    int mid = (segTree[i].l + segTree[i].r) / 2;
    if (r <= mid)return query(i << 1, l, r, p);
    else if (l > mid)return query((i << 1) | 1, l, r, p);
    else return (query(i << 1, l, mid, p) + query((i << 1) | 1, mid + 1, r, p)) % MOD;
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n, m;
    while (scanf("%d%d", &n, &m) == 2)
    {
        if (n == 0 && m == 0)break;
        build(1, 1, n);
        int type, x, y, c;
        while (m--)
        {
            scanf("%d%d%d%d", &type, &x, &y, &c);
            if (type == 4)printf("%d\n", query(1, x, y, c));
            else update(1, x, y, type, c);
        }
    }
    return 0;
}