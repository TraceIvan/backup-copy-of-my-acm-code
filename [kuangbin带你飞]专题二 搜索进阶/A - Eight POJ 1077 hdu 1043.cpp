
#include<iostream>
#include<vector>
#include<memory.h>
using namespace std;
const int maxst = 500000;
int st[maxst][9];
int goal[9];
int Head[maxst], Next[maxst];//存的是st[i]，i的值
int dis[maxst];//走到第st[i]这种状态的步数
int dx[] = { 1,-1,0,0 };
int dy[] = { 0,0,1,-1 };
char c[] = { 'd','u','r','l' };
struct Dir
{
    char c;
    int father;
    Dir(char cc = 'u', int f = 1) :c(cc), father(f)
    {
    }
}dir[maxst];
int Hash(int* st)
{
    int v = 0;
    for (int i = 0; i < 9; i++) v = v * 10 + st[i];
    return v%maxst;
}
bool Judge(int p)
{
    int val = Hash(st[p]);//st[p]这种状态在Head里的位置
    int pos = Head[val];//Head[val]里保存的状态的下标
    while (pos)
    {
        if (!memcmp(st[pos], st[p], sizeof(st[p]))) return false;
        pos = Next[pos];//下一个下标
    }
    Next[p] = Head[val];
    Head[val] = p;
    return true;
}
int BFS()
{
    memset(Head, 0, sizeof(Head));
    memset(Next, 0, sizeof(Next));
    memset(dis, 0, sizeof(dis));
    memset(dir, 0, sizeof(dir));
    int cur = 1, real = 2;//当前图；最后一个图的下一个位置
    while (cur < real)//没有穷举完所有的状态
    {
        if (!memcmp(goal, st[cur], sizeof(goal)))
            return cur;
        int zero;
        for (zero = 0; zero < 9; zero++) if (st[cur][zero] == 0) break;
        int x = zero / 3, y = zero % 3;
        for (int i = 0; i < 4; i++)
        {//对于某种状态，至多有四种可行的走法，若未走过，则加入st
            int nx = x + dx[i];
            int ny = y + dy[i];
            int ps = nx * 3 + ny;
            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3)
            {
                memcpy(st[real], st[cur], sizeof(st[cur]));
                st[real][zero] = st[real][ps];
                st[real][ps] = 0;
                if (Judge(real))
                {
                    dis[real] = dis[cur] + 1;
                    dir[real].c = c[i];
                    dir[real].father = cur;
                    real++;
                }
            }
        }
        cur++;//向后查询下一张图
    }
    return 0;
}
void Print(int p)
{
    if (p != 1)
    {
        Print(dir[p].father);
        printf("%c", dir[p].c);
    }
}
int main()
{
    char a;
    while (cin >> a)
    {
        memset(st, 0, sizeof(st));
        if (a != 'x')
        {
            st[1][0] = a - '0';
        }
        else st[1][0] = 0;
        for (int i = 1; i < 9; i++)
        {
            cin >> a;
            if (a != 'x')
            {
                st[1][i] = a - '0';
            }
            else st[1][i] = 0;
        }
        for (int i = 0; i < 9; i++) goal[i] = i + 1;
        goal[8] = 0;
        int pos = BFS();
        if (pos == 0) printf("unsolvable\n");
        else
        {
            Print(pos);
            printf("\n");
        }
    }
    return 0;
}