//题意：给你一个长度为n(1<=n<=20000)的数字串。如果一个串在母串出现的次数大于一次那么这个串就是母串的重复子串。子串的每个位置同时加上一个数字重复出现在另一个位置也算重复。先在问这个母串最长的不相交即没有重复元素的重复子串的最大长度。
#include<iostream>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
const int MAX = 20050;

int n, num[MAX];
int sa[MAX], Rank[MAX], height[MAX];
int tp[MAX], wb[MAX], wv[MAX], tax[MAX];
//sa:所有后缀的字典序中排第i位的在原串的起始位置为sa[i]
//Rank：原串中第i个位置开始的后缀在字典序的排名
//heiht:字典序中第i个和i-1个的后缀的最长公共前缀
//tp:rank的辅助数组(计数排序中的第二关键字),与SA意义一样。
//wb:
//wv:
//tax:基数排序辅助数组
int cmp(int *r, int a, int b, int l)
{//通过二元组两个下标的比较，确定两个子串是否相同
    return r[a] == r[b] && r[a + l] == r[b + l];
}

void getsa(int *r, int n, int m)
{//m为ASCII码的范围 
    int i, j, p, *x = tp, *y = wb, *t;
    //基数排序
    for (i = 0; i < m; i++) tax[i] = 0;
    for (i = 0; i < n; i++) tax[x[i] = r[i]] ++;
    for (i = 1; i < m; i++) tax[i] += tax[i - 1];
    for (i = n - 1; i >= 0; i--) sa[--tax[x[i]]] = i;//倒着枚举保证相对顺序  

    for (j = 1, p = 1; p < n; j *= 2, m = p)
    {//把子串长度翻倍,更新rank
        //j:当前一个字串的长度
        //m:当前离散后的排名种类数
        for (p = 0, i = n - j; i < n; i++) y[p++] = i;
        for (i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;//按第二关键字排序.y[i]表示第二关键字排名第i的后缀起始位置  

        for (i = 0; i < n; i++) wv[i] = x[y[i]];//暂存

        for (i = 0; i < m; i++) tax[i] = 0;
        for (i = 0; i < n; i++) tax[wv[i]] ++;//x[i]表示起始位置为i的后缀的第一关键字排序
        for (i = 1; i < m; i++) tax[i] += tax[i - 1];
        for (i = n - 1; i >= 0; i--) sa[--tax[wv[i]]] = y[i];//接着按第一关键字排序 

        for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
        {////x[i]存排名第i后缀的排名 
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
        }
    }
}

void calHeight(int *r, int n)
{
    int i, j, k = 0;
    for (i = 1; i <= n; i++) Rank[sa[i]] = i;
    for (i = 0; i < n; height[Rank[i++]] = k)
    {
        for (k ? k-- : 0, j = sa[Rank[i] - 1]; r[i + k] == r[j + k]; k++);
    }
}

bool valid(int len)
{
    int i = 2, ma, mi;//区间下界和上界  
    while (1)
    {
        while (i <= n && height[i] < len) i++;
        if (i > n) break;
        ma = sa[i - 1];
        mi = sa[i - 1];
        while (i <= n && height[i] >= len)
        {
            ma = max(ma, sa[i]);
            mi = min(mi, sa[i]);
            i++;
        }
        if (ma - mi >= len) return true;
    }
    return false;
}

int main()
{
    int i, ans;
    while (scanf("%d", &n) && n != 0)
    {
        for (i = 0; i < n; i++)
        {
            scanf("%d", &num[i]);
        }
        if (n < 10)
        {//如果小于10，则不相交重复子串字串长度不超过5，不符合题意
            printf("0\n");
            continue;
        }
        n--;
        for (i = 0; i < n; i++)
        {
            num[i] = num[i + 1] - num[i] + 89;
        }
        num[n] = 0;
        getsa(num, n + 1, 200);
        calHeight(num, n);

        int low = 4, high = (n - 1) / 2, mid;
        while (low < high)
        {
            mid = (low + high + 1) / 2;
            if (valid(mid))
            {
                low = mid;
            }
            else
            {
                high = mid - 1;
            }
        }
        ans = low < 4 ? 0 : low + 1;//加回1
        printf("%d\n", ans);
    }
    return 0;
}