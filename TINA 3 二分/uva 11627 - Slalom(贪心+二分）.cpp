#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int W, vh, N,S;
const int maxn = 100010;
const int maxs = 1000010;
struct Gate
{
    int x, y;
}gt[maxn];
int s[maxs];
bool Cmp(const Gate&a, const Gate&b)
{
    return a.y < b.y;
}
bool Judge(int v)
{
    double l = gt[N-1].x, r = gt[N-1].x + W;
    for (int i = N - 2; i >= 0; i--)//�������ϵݹ飬�ҳ�ÿ�οɴ����䣬ͬʱ�ж��Ƿ���С������У�����µ�ǰ����
    {
        int th = gt[i + 1].y - gt[i].y;
        double tt = 1.0*th / v;
        double tl = l - tt*vh;
        double tr = r + tt*vh;
        if (tr < gt[i].x) return false;
        if (tl > gt[i].x + W) return false;
        if (gt[i].x> tl) l = gt[i].x;
        else l = tl;
        if (gt[i].x + W<tr) r = gt[i].x + W;
        else r = tr;
    }
    return true;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &W, &vh, &N);
        for (int i = 0; i < N; i++) scanf("%d%d", &gt[i].x, &gt[i].y);
        scanf("%d", &S);
        for (int i = 0; i < S; i++) scanf("%d", &s[i]);
        sort(s, s+S);
        sort(gt, gt + N, Cmp);
        if (!Judge(s[0])) printf("IMPOSSIBLE\n");//������ٶ�������(��ˮƽ�ɴ��������)�������У�������ٶȱ�����Ķ�������
        else if(Judge(s[S-1]))//����ٶ����Ķ����У����������ж��ٶȱ���С��
        {
            printf("%d\n", s[S-1]);
        }
        else
        {
            int L = 0, R = S-1;
            while (R >= L)
            {
                int mid = (L + R) / 2;
                if (Judge(s[mid])) L = mid+1;
                else R = mid - 1;
            }
            printf("%d\n", s[R]);
        }
    }
    return 0;
}
