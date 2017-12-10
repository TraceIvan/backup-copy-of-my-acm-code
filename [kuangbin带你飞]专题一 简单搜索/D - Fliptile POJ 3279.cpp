//最多15位，用2进制状态压缩。枚举第一层的反转情况。第一层确定，后面反转状态的都会确定下来
#include<iostream>
using namespace std;
const int maxn = 16;
const int maxp = 16 * 16;
int init[maxn];//存初始状态
int flipstate[maxn];//存反转状态
int state[maxn];//存中间的状态
int ans[maxn],steps;//存结果
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
            }//由于我们按照第一行反转状态从小到大DFS，所以如果相等，肯定前面已经保存的字典序小，所以不用再进行判断及赋值操作
        }
        return;
    }
    flipstate[r] = 0;

    for (int i = m-1; i>=0; --i)
    {//从左往右遍历
        if (state[r - 1] & (1 << i))//前一行为1
        {
            flipstate[r] |= 1 << i;//该行灯反转
            state[r - 1] ^= (1 << i);//保存反转后对格子的影响
            state[r] ^= (1 << i);
            if (i + 1 <= m - 1) state[r] ^= (1 << (i + 1));
            if(i-1>=0) state[r] ^= (1 << (i - 1));
            if (r + 1 < n) state[r + 1] ^= (1 << i);
            cnt++;//反转次数累加
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