//���15λ����2����״̬ѹ����ö�ٵ�һ��ķ�ת�������һ��ȷ�������淴ת״̬�Ķ���ȷ������
#include<iostream>
using namespace std;
const int maxn = 16;
const int maxp = 16 * 16;
int init[maxn];//���ʼ״̬
int flipstate[maxn];//�淴ת״̬
int state[maxn];//���м��״̬
int ans[maxn],steps;//����
int n, m;
void DFS(int r, int cnt)
{
    if (r == n)
    {
        if (state[n - 1] == 0)
        {
            if (cnt < steps)
            {
                for (int i = 0; i < n; i++) ans[i] = flipstate[i];
                steps = cnt;
            }//�������ǰ��յ�һ�з�ת״̬��С����DFS�����������ȣ��϶�ǰ���Ѿ�������ֵ���С�����Բ����ٽ����жϼ���ֵ����
        }
        return;
    }
    flipstate[r] = 0;

    for (int i = m-1; i>=0; --i)
    {//�������ұ���
        if (state[r - 1] & (1 << i))//ǰһ��Ϊ1
        {
            flipstate[r] |= 1 << i;//���еƷ�ת
            state[r - 1] ^= (1 << i);//���淴ת��Ը��ӵ�Ӱ��
            state[r] ^= (1 << i);
            if (i + 1 <= m - 1) state[r] ^= (1 << (i + 1));
            if(i-1>=0) state[r] ^= (1 << (i - 1));
            if (r + 1 < n) state[r + 1] ^= (1 << i);
            cnt++;//��ת�����ۼ�
        }
    }
    DFS(r + 1, cnt);
}
void Solve()
{
    int total = (1 << m) - 1;
    steps = maxp;
    for (int st = 0; st <= total; st++)
    {
        flipstate[0] = st;
        memcpy(state, init, sizeof(init));
        int cnt = 0;
        for (int i = m - 1; i >= 0; --i)
        {
            if (st&(1 << i))
            {
                state[0] ^= (1 << i);
                if (i + 1 <= m - 1)state[0] ^= (1 << (i + 1));
                if (i - 1 >= 0) state[0] ^= (1 << (i - 1));
                state[1] ^= (1 << i);
                cnt++;
            }
        }
        DFS(1, cnt);
    }
}
int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        memset(init, 0, sizeof(init));
        for (int i = 0; i < n; i++)
        {
            for (int j = m - 1; j >= 0; --j)
            {
                int num;
                scanf("%d", &num);
                if (num == 1) init[i] |= (1 << j);
            }
        }
        Solve();
        if (steps == maxp) printf("IMPOSSIBLE\n");
        else
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = m - 1; j >= 0; --j)
                {
                    if (j < m - 1) printf(" ");
                    if (ans[i] & (1 << j))printf("1");
                    else printf("0");
                }
                printf("\n");
            }
        }
    }
    return 0;
}