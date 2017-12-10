#include<iostream>
#include<string>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

const int maxn = 400000;
const char* DIR1 = "udlr";//上下左右
const char* DIR2 = "durl";//下上右左，因为从终点开始广搜，然后从中间状态要走到终点，方向反

int kthash[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320 }; //康拓展开的阶乘值

int x; //初始状态x的位置

int dir[] = { -3, 3, -1, 1 };//在数组里的位置变化。向上走位置-3，向下走位置+3，向左走位置-1，向右走位置+1

int vis1[maxn];//起点广搜标记
int vis2[maxn];//终点广搜标记

char ss[] = "123456780";//目标即最终状态
char str[10];//初始状态

struct Node
{
    int x;//'x'的位置
    char str[10];//棋子的状态
};//用于广搜时队列的元素

struct Step
{
    int cnt;
    char dir;
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


void printfff(int x)  //追溯到起点输出路径
{
    if (pre[x].cnt == -1)  return;
    printfff(pre[x].cnt);
    cout << pre[x].dir;
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
    p1.x = x;             //初始x的位置
                          //cout << p1.str << endl;
    strcpy(p2.str, ss);   //最终状态
    p2.x = 8;             //最终x的位置
                          //cout << p2.str << endl;
    q1.push(p1);
    q2.push(p2);
    vis1[Hush(str)] = 1;//为0表示没有访问，否则表示pre[]访问位置
    vis2[Hush(ss)] = 2;
    pre[1].cnt = -1;  //起点标记
    pre[2].cnt = -1;  //终点标记
    while (!q1.empty() && !q2.empty())
    {
        Node u = q1.front();
        q1.pop();
        int p = Hush(u.str);
        if (vis2[p])  //在终点广搜中出现过
        {
            printfff(vis1[p]);//先打印从起点到该点
            int k = vis2[p];
            while (pre[k].cnt != -1)//打印从该点到终点
            {
                cout << pre[k].dir;
                k = pre[k].cnt;
            }
            cout << endl;
            return;
        }
        else //未找到目标状态
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
                q1.push(u2);
            }
        }

        u = q2.front();
        q2.pop();
        p = Hush(u.str);
        if (vis1[p])
        {
            printfff(vis1[p]);
            int k = vis2[p];
            while (pre[k].cnt != -1)
            {
                cout << pre[k].dir;
                k = pre[k].cnt;
            }
            cout << endl;
            return;
        }
        else //未找到目标状态
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
                q2.push(u2);
            }
        }
    }
    cout << "unsolvable" << endl;
}


int main()
{

    char s[40];
    while (gets_s(s,40))
    {
        int k = 0;
        int t = 0;
        for (int i = 0; s[i] !='\0'; i++)
        {
            if (s[i] == ' ')continue;
            if (s[i] == 'x')
            {
                str[k] = '0'; 
                x = k;
            }
            else str[k] = s[i];
            k++;
        }
        str[k] = '\0';

        for (int i = 0; i<9; i++)  //逆序数判断是否可行
        {
            if (str[i] == '0')continue;
            for (int j = 0; j<i; j++)
            {
                if (str[j] == '0')continue;
                if (str[j]>str[i])t++;
            }
        }
        if (t & 1) cout << "unsolvable" << endl;//逆序数为奇数，则不可行
        else bfs();
    }
    return 0;
}