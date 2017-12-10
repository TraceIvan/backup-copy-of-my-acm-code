//���⣺����һ������Ϊn(1<=n<=20000)�����ִ������һ������ĸ�����ֵĴ�������һ����ô���������ĸ�����ظ��Ӵ����Ӵ���ÿ��λ��ͬʱ����һ�������ظ���������һ��λ��Ҳ���ظ������������ĸ����Ĳ��ཻ��û���ظ�Ԫ�ص��ظ��Ӵ�����󳤶ȡ�
#include<iostream>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
const int MAX = 20050;

int n, num[MAX];
int sa[MAX], Rank[MAX], height[MAX];
int tp[MAX], wb[MAX], wv[MAX], tax[MAX];
//sa:���к�׺���ֵ������ŵ�iλ����ԭ������ʼλ��Ϊsa[i]
//Rank��ԭ���е�i��λ�ÿ�ʼ�ĺ�׺���ֵ��������
//heiht:�ֵ����е�i����i-1���ĺ�׺�������ǰ׺
//tp:rank�ĸ�������(���������еĵڶ��ؼ���),��SA����һ����
//wb:
//wv:
//tax:��������������
int cmp(int *r, int a, int b, int l)
{//ͨ����Ԫ�������±�ıȽϣ�ȷ�������Ӵ��Ƿ���ͬ
    return r[a] == r[b] && r[a + l] == r[b + l];
}

void getsa(int *r, int n, int m)
{//mΪASCII��ķ�Χ 
    int i, j, p, *x = tp, *y = wb, *t;
    //��������
    for (i = 0; i < m; i++) tax[i] = 0;
    for (i = 0; i < n; i++) tax[x[i] = r[i]] ++;
    for (i = 1; i < m; i++) tax[i] += tax[i - 1];
    for (i = n - 1; i >= 0; i--) sa[--tax[x[i]]] = i;//����ö�ٱ�֤���˳��  

    for (j = 1, p = 1; p < n; j *= 2, m = p)
    {//���Ӵ����ȷ���,����rank
        //j:��ǰһ���ִ��ĳ���
        //m:��ǰ��ɢ�������������
        for (p = 0, i = n - j; i < n; i++) y[p++] = i;
        for (i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;//���ڶ��ؼ�������.y[i]��ʾ�ڶ��ؼ���������i�ĺ�׺��ʼλ��  

        for (i = 0; i < n; i++) wv[i] = x[y[i]];//�ݴ�

        for (i = 0; i < m; i++) tax[i] = 0;
        for (i = 0; i < n; i++) tax[wv[i]] ++;//x[i]��ʾ��ʼλ��Ϊi�ĺ�׺�ĵ�һ�ؼ�������
        for (i = 1; i < m; i++) tax[i] += tax[i - 1];
        for (i = n - 1; i >= 0; i--) sa[--tax[wv[i]]] = y[i];//���Ű���һ�ؼ������� 

        for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
        {////x[i]��������i��׺������ 
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
    int i = 2, ma, mi;//�����½���Ͻ�  
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
        {//���С��10�����ཻ�ظ��Ӵ��ִ����Ȳ�����5������������
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
        ans = low < 4 ? 0 : low + 1;//�ӻ�1
        printf("%d\n", ans);
    }
    return 0;
}