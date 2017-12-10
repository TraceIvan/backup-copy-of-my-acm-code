#include<iostream>
#include<string>
#include<cstring>
#include<queue>
#include<algorithm>
#include<cstdio>
using namespace std;

const int maxn = 500000;
const char* DIR1 = "udlr";//��������
const char* DIR2 = "durl";//����������Ϊ���յ㿪ʼ���ѣ�Ȼ����м�״̬Ҫ�ߵ��յ㣬����

int kthash[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320 }; //����չ���Ľ׳�ֵ

int dir[] = { -3, 3, -1, 1 };//���������λ�ñ仯��������λ��-3��������λ��+3��������λ��-1��������λ��+1

int vis1[maxn];//�����ѱ��
int vis2[maxn];//�յ���ѱ��

char ss[10];//Ŀ�꼴����״̬
char str[10];//��ʼ״̬
int xstr; //��ʼ״̬x��λ��
int xed;//����״̬x��λ��

int Case = 1;

bool first = false;
string ans;

struct Node
{
    int x;//'x'��λ��
    char str[10];//���ӵ�״̬
};//���ڹ���ʱ���е�Ԫ��

struct Step
{
    int cnt;//pre[]λ��
    char dir;
    int stp;
}pre[maxn];//��¼·��
int Hush(char* a)  //���㿵��չ��ֵ
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


void Sprintf(int x,string &s)  //׷�ݵ�������·��
{
    if (pre[x].cnt == -1)  return;
    Sprintf(pre[x].cnt,s);
    s+= pre[x].dir;
}

int judge(int x, int i)   //�ж��Ƿ�Խ�磬xΪ'0'(����'x')��һά�����λ��
{
    int xx = x / 3;  //��
    int yy = x % 3;  //��
    if (i == 3)//������
    {
        int yyy = yy + 1;
        if (yyy > 2)  return 0;
    }
    if (i == 2)//������
    {
        int yyy = yy - 1;
        if (yyy < 0)   return 0;
    }
    if (i == 1)//������
    {
        int xxx = xx + 1;
        if (xxx>2)    return 0;
    }
    if (i == 0)//������
    {
        int xxx = xx - 1;
        if (xxx < 0) return 0;
    }
    return 1;
}

void bfs()
{
    memset(vis1, 0, sizeof(vis1));//�����BFS�������
    memset(vis2, 0, sizeof(vis2));//���յ�BFS�������

    queue<Node> q1, q2;//q1���BFS��q2�յ�BFS
    Node p1, p2;

    int count = 2;
    strcpy(p1.str, str);  //��ʼ״̬
    p1.x = xstr;             //��ʼx��λ��
                          //cout << p1.str << endl;
    strcpy(p2.str, ss);   //����״̬
    p2.x = xed;             //����x��λ��
                          //cout << p2.str << endl;
    q1.push(p1);
    q2.push(p2);
    vis1[Hush(str)] = 1;//Ϊ0��ʾû�з��ʣ������ʾpre[]����λ��
    vis2[Hush(ss)] = 2;
    pre[1].cnt = -1;  //�����
    pre[2].cnt = -1;  //�յ���
    pre[1].stp = 0;
    pre[2].stp = 0;
    while (!q1.empty() && !q2.empty()&&first)
    {
        Node u = q1.front();
        q1.pop();
        int p = Hush(u.str);
        if (vis2[p])  //���յ�����г��ֹ�
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
        else//δ�ҵ�Ŀ��״̬���һ���ҵ���ڶ����ҵ�������ȣ�ֱ���ҵ����ȴ��ڵ�һ��
        {
            Node u2;
            for (int i = 0; i < 4; i++)
            {
                u2 = u;
                if (!judge(u.x, i))  continue;
                int xx = u.x + dir[i]; //x���µ�ַ
                swap(u2.str[u.x], u2.str[xx]);
                u2.x = xx;
                int v = Hush(u2.str);
                if (vis1[v])  continue; //�ѷ���
                vis1[v] = ++count;
                pre[count].dir = DIR1[i]; //��¼����
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
        else//δ�ҵ�Ŀ��״̬���һ���ҵ���ڶ����ҵ�������ȣ�ֱ���ҵ����ȴ��ڵ�һ��
        {
            Node u2;
            for (int i = 0; i < 4; i++)
            {
                u2 = u;
                if (!judge(u.x, i))  continue;
                int xx = u.x + dir[i]; //x���µ�ַ
                swap(u2.str[u.x], u2.str[xx]);
                u2.x = xx;
                int v = Hush(u2.str);
                if (vis2[v])  continue; //�ѷ���
                vis2[v] = ++count;
                pre[count].dir = DIR2[i]; //��¼����
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