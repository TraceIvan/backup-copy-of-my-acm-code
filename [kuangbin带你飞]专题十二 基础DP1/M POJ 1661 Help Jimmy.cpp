#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
struct node
{
    int x1;//�������
    int x2;//�����Ҳ�
    int h;//���ڸ߶�
};
node op[1010];
int dp[20010][2];
//dp[i][0]��ʾ��i��ƽ̨���Ϊ��㵽��������ʱ�䣬dp[i][1]��ʾ��i��ƽ̨�ұ�Ϊ��㵽��������ʱ��
bool cmp(node a, node b)
{//���߶ȴӵ͵���
    return a.h < b.h;
}
const int inf = 0x7f7f7f7f;
int main()
{
    int t;
    int n, x, y, maxn;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d%d%d", &n, &x, &y, &maxn);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d%d", &op[i].x1, &op[i].x2, &op[i].h);
        }
        sort(op + 1, op + n + 1, cmp);

        // 0 ��
        // 1 ��
        dp[1][0] = dp[1][1] = op[1].h;
        op[n + 1].x1 = op[n + 1].x2 = x;
        op[n + 1].h = y;// op[n+1] ��ʵ����������꣨x,y��,��ߵĿ�ʼ���ĵط�;

        for (int i = 2; i <= n + 1; i++)
        {//�Ӹ߶ȵ͵�����DP
            dp[i][0] = dp[i][1] = inf;
            int flag0 = 0; // ���ڱ������˵�
            int flag1 = 0; // ���ڱ������˵�
            int tmp;
            for (int j = i - 1; j>0; j--) // ����ע�����������Ϊ�������������а��ӵ�ס�Ļ���û�������������ˡ�
            {
                if (op[i].h - op[j].h > maxn) continue;
                if (op[j].x1 <= op[i].x1 && op[j].x2 >= op[i].x1 &&flag0 == 0)
                {//���Դӵ�i��ƽ̨�����������j��ƽ̨��
                    tmp = min(dp[j][0] - op[j].x1 + op[i].x1, dp[j][1] - op[i].x1 + op[j].x2);
                    dp[i][0] = min(dp[i][0], tmp + op[i].h - op[j].h);
                    //tmp��ʾ������j��ƽ̨������������ߵ������ʱ�����Сֵ
                    //tmp + op[i].h - op[j].hΪ�ټ��ϴӵ�i��ƽ̨���������j��ƽ̨����Ҫ��ʱ��
                    flag0 = 1; // ��ʾ�Ѿ����ܼ����������ˣ���Ϊ�Ѿ��а�����
                }
                if (op[j].x1 <= op[i].x2 && op[j].x2 >= op[i].x2&&flag1 == 0)
                {//���Դӵ�i��ƽ̨���Ҳ�������j��ƽ̨��
                    tmp = min(dp[j][0] - op[j].x1 + op[i].x2, dp[j][1] - op[i].x2 + op[j].x2);
                    dp[i][1] = min(dp[i][1], tmp + op[i].h - op[j].h);
                    flag1 = 1; // ����ͬ��
                }
                if (flag0 == 1 && flag1 == 1)break;
            }
            if (flag0 == 0 && op[i].h <= maxn)
            {//ƽ̨i�����û���������ӣ����Ҿ������ĸ߶�С�ڵ������ĸ߶�
                dp[i][0] = min(dp[i][0], op[i].h);
            }
            if (flag1 == 0 && op[i].h <= maxn)
            {//ƽ̨i�Ҳ���û���������ӣ����Ҿ������ĸ߶�С�ڵ������ĸ߶�
                dp[i][1] = min(dp[i][1], op[i].h);
            }// �����ж��ǲ��ǿ���ֱ�����������ϡ�
             //cout << dp[i][0] << " " << dp[i][1] << endl;
        }
        int cc = min(dp[n + 1][0], dp[n + 1][1]);
        cout << cc << endl;
    }
    return 0;
}