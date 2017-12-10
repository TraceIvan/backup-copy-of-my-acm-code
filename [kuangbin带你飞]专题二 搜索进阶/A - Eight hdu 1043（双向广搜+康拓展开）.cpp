#include<iostream>
#include<string>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

const int maxn = 400000;
const char* DIR1 = "udlr";//��������
const char* DIR2 = "durl";//����������Ϊ���յ㿪ʼ���ѣ�Ȼ����м�״̬Ҫ�ߵ��յ㣬����

int kthash[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320 }; //����չ���Ľ׳�ֵ

int x; //��ʼ״̬x��λ��

int dir[] = { -3, 3, -1, 1 };//���������λ�ñ仯��������λ��-3��������λ��+3��������λ��-1��������λ��+1

int vis1[maxn];//�����ѱ��
int vis2[maxn];//�յ���ѱ��

char ss[] = "123456780";//Ŀ�꼴����״̬
char str[10];//��ʼ״̬

struct Node
{
    int x;//'x'��λ��
    char str[10];//���ӵ�״̬
};//���ڹ���ʱ���е�Ԫ��

struct Step
{
    int cnt;
    char dir;
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


void printfff(int x)  //׷�ݵ�������·��
{
    if (pre[x].cnt == -1)  return;
    printfff(pre[x].cnt);
    cout << pre[x].dir;
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
    p1.x = x;             //��ʼx��λ��
                          //cout << p1.str << endl;
    strcpy(p2.str, ss);   //����״̬
    p2.x = 8;             //����x��λ��
                          //cout << p2.str << endl;
    q1.push(p1);
    q2.push(p2);
    vis1[Hush(str)] = 1;//Ϊ0��ʾû�з��ʣ������ʾpre[]����λ��
    vis2[Hush(ss)] = 2;
    pre[1].cnt = -1;  //�����
    pre[2].cnt = -1;  //�յ���
    while (!q1.empty() && !q2.empty())
    {
        Node u = q1.front();
        q1.pop();
        int p = Hush(u.str);
        if (vis2[p])  //���յ�����г��ֹ�
        {
            printfff(vis1[p]);//�ȴ�ӡ����㵽�õ�
            int k = vis2[p];
            while (pre[k].cnt != -1)//��ӡ�Ӹõ㵽�յ�
            {
                cout << pre[k].dir;
                k = pre[k].cnt;
            }
            cout << endl;
            return;
        }
        else //δ�ҵ�Ŀ��״̬
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
        else //δ�ҵ�Ŀ��״̬
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

        for (int i = 0; i<9; i++)  //�������ж��Ƿ����
        {
            if (str[i] == '0')continue;
            for (int j = 0; j<i; j++)
            {
                if (str[j] == '0')continue;
                if (str[j]>str[i])t++;
            }
        }
        if (t & 1) cout << "unsolvable" << endl;//������Ϊ�������򲻿���
        else bfs();
    }
    return 0;
}