#include<iostream>
#include<string>
#include<cstring>
#include<queue>
#include<algorithm>
#include<cstdio>
using namespace std;

const int maxn = 500000;
const char* DIR1 = "udlr";//上下左右
const char* DIR2 = "durl";//下上右左，因为从终点开始广搜，然后从中间状态要走到终点，方向反

int kthash[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320 }; //康拓展开的阶乘值

int dir[] = { -3, 3, -1, 1 };//在数组里的位置变化。向上走位置-3，向下走位置+3，向左走位置-1，向右走位置+1

int vis1[maxn];//起点广搜标记
int vis2[maxn];//终点广搜标记

char ss[10];//目标即最终状态
char str[10];//初始状态
int xstr; //初始状态x的位置
int xed;//最终状态x的位置

int Case = 1;

bool first = false;
string ans;

struct Node
{
    int x;//'x'的位置
    char str[10];//棋子的状态
};//用于广搜时队列的元素

struct Step
{
    int cnt;//pre[]位置
    char dir;
    int stp;
}pre[maxn];//记录路径
int Hush(char* a)  //计算康托展开值
{
    int s = 0, i, j, k;
    for (i = 0; i<9; i++)
    {
        k = 0;
        for (j = 0; j<i; j++)
            if (a[j]>a[i])k++;
        s += k*kthash[i];
    }
    return s;
}


void Sprintf(int x,string &s)  //追溯到起点输出路径
{
    if (pre[x].cnt == -1)  return;
    Sprintf(pre[x].cnt,s);
    s+= pre[x].dir;
}

int judge(int x, int i)   //判断是否越界，x为'0'(代表'x')在一维数组的位置
{
    int xx = x / 3;  //行
    int yy = x % 3;  //列
    if (i == 3)//向右走
    {
        int yyy = yy + 1;
        if (yyy > 2)  return 0;
    }
    if (i == 2)//向左走
    {
        int yyy = yy - 1;
        if (yyy < 0)   return 0;
    }
    if (i == 1)//向下走
    {
        int xxx = xx + 1;
        if (xxx>2)    return 0;
    }
    if (i == 0)//向上走
    {
        int xxx = xx - 1;
        if (xxx < 0) return 0;
    }
    return 1;
}

void bfs()
{
    memset(vis1, 0, sizeof(vis1));//从起点BFS标记数组
    memset(vis2, 0, sizeof(vis2));//从终点BFS标记数组

    queue<Node> q1, q2;//q1起点BFS，q2终点BFS
    Node p1, p2;

    int count = 2;
    strcpy(p1.str, str);  //初始状态
    p1.x = xstr;             //初始x的位置
                          //cout << p1.str << endl;
    strcpy(p2.str, ss);   //最终状态
    p2.x = xed;             //最终x的位置
                          //cout << p2.str << endl;
    q1.push(p1);
    q2.push(p2);
    vis1[Hush(str)] = 1;//为0表示没有访问，否则表示pre[]访问位置
    vis2[Hush(ss)] = 2;
    pre[1].cnt = -1;  //起点标记
    pre[2].cnt = -1;  //终点标记
    pre[1].stp = 0;
    pre[2].stp = 0;
    while (!q1.empty() && !q2.empty()&&first)
    {
        Node u = q1.front();
        q1.pop();
        int p = Hush(u.str);
        if (vis2[p])  //在终点广搜中出现过
        {
            int step = pre[vis1[p]].stp + pre[vis2[p]].stp;
            string s;
            first = false;
            Sprintf(vis1[p], s);
            ans = s;
            int k = vis2[p];
            while (pre[k].cnt != -1)
            {
                ans += pre[k].dir;
                k = pre[k].cnt;
            }
            break;
        }
        else//未找到目标状态或第一次找到或第二次找到长度相等，直到找到长度大于第一次
        {
            Node u2;
            for (int i = 0; i < 4; i++)
            {
                u2 = u;
                if (!judge(u.x, i))  continue;
                int xx = u.x + dir[i]; //x的新地址
                swap(u2.str[u.x], u2.str[xx]);
                u2.x = xx;
                int v = Hush(u2.str);
                if (vis1[v])  continue; //已访问
                vis1[v] = ++count;
                pre[count].dir = DIR1[i]; //记录方向
                pre[count].cnt = vis1[p];
                pre[count].stp = pre[vis1[p]].stp + 1;
                q1.push(u2);
            }
        }

        u = q2.front();
        q2.pop();
        p = Hush(u.str);
        if (vis1[p])
        {
            int step = pre[vis1[p]].stp + pre[vis2[p]].stp;
            string s;
            first = false;
            Sprintf(vis1[p], s);
            ans = s;
            int k = vis2[p];
            while (pre[k].cnt != -1)
            {
                ans += pre[k].dir;
                k = pre[k].cnt;
            }
            break;
        }
        else//未找到目标状态或第一次找到或第二次找到长度相等，直到找到长度大于第一次
        {
            Node u2;
            for (int i = 0; i < 4; i++)
            {
                u2 = u;
                if (!judge(u.x, i))  continue;
                int xx = u.x + dir[i]; //x的新地址
                swap(u2.str[u.x], u2.str[xx]);
                u2.x = xx;
                int v = Hush(u2.str);
                if (vis2[v])  continue; //已访问
                vis2[v] = ++count;
                pre[count].dir = DIR2[i]; //记录方向
                pre[count].cnt = vis2[p];
                pre[count].stp = pre[vis2[p]].stp + 1;
                q2.push(u2);
            }
        }
    }
    while (!q1.empty())
    {
        Node n1= q1.front();
        q1.pop();
        int pos = Hush(n1.str);
        if (!vis2[pos]) continue;
        int step = pre[vis1[pos]].stp + pre[vis2[pos]].stp;
        string s;
        Sprintf(vis1[pos], s);
        int k = vis2[pos];
        while (pre[k].cnt != -1)
        {
            s += pre[k].dir;
            k = pre[k].cnt;
        }
        if (s < ans) ans = s;
    }
    while (!q2.empty())
    {
        Node n2 = q2.front();
        q2.pop();
        int pos = Hush(n2.str);
        if (!vis1[pos]) continue;
        int step = pre[vis1[pos]].stp + pre[vis2[pos]].stp;
        string s;
        Sprintf(vis1[pos], s);
        int k = vis2[pos];
        while (pre[k].cnt != -1)
        {
            s += pre[k].dir;
            k = pre[k].cnt;
        }
        if (s < ans) ans = s;
    }
    printf("Case %d: %d\n", Case, ans.size());
    printf("%s\n", ans.c_str());
}


int main()
{
    freopen("in.txt", "r", stdin);
    freopen("outwrong.txt", "w", stdout);
    int t;
    cin >> t;
    while(t--)
    {
        first = true;
        scanf("%s", str);
        scanf("%s", ss);
        for (int i = 0; i < 9; i++)
        {
            if (str[i] == 'X')
            {
                str[i] = '0';
                xstr = i;
                break;
            }
        }
        for (int i = 0; i < 9; i++)
        {
            if (ss[i] == 'X')
            {
                ss[i] = '0';
                xed = i;
                break;
            }
        }
        bfs();
        Case++;
    }
    return 0;
}