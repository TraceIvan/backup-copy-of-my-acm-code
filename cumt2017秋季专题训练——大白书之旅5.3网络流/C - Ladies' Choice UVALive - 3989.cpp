//�ȶ���������

#include<iostream>
#include<queue>
#include<cstdio>
using namespace std;
const int maxn = 1010;

struct gs//Gale - Shapley�㷨
{//Ůʿ����
    int n;
    int girl_pre[maxn][maxn];
    int boy_pre[maxn][maxn];
    int girl_match[maxn], boy_match[maxn];
    int next[maxn];
    queue<int>q;//δ��ʼѡ���Ů��

    void engage(int girl, int boy)
    {//ƥ��
        int pre = boy_match[boy];
        if (pre)
        {
            girl_match[pre] = 0;
            q.push(pre);
        }
        girl_match[girl] = boy;
        boy_match[boy] = girl;
    }

    void read()
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++) scanf("%d", &girl_pre[i][j]);
            next[i] = 1;//�´εȴ�ѡ��
            girl_match[i] = 0;
            q.push(i);//����δѡ���Ů������
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                int p;
                scanf("%d", &p);
                boy_pre[i][p] = j;//��i��������pŮ��������
            }
            boy_match[i] = 0;
        }
    }

    void solve()
    {
        while (!q.empty())
        {
            int girl = q.front();
            q.pop();
            int boy = girl_pre[girl][next[girl]++];
            if (!boy_match[boy]) engage(girl, boy);//�����Ů��ϲ�����к�û�б�ѡ
            else if (boy_pre[boy][girl] < boy_pre[boy][boy_match[boy]]) engage(girl, boy);//���߸�Ů��ϲ�����к��ĵ�ǰƥ���Ů��ϲ���̶Ȳ�����Ů��
            else q.push(girl);//�ȴ��´�ƥ��
        }
    }

    void print()
    {
        for (int i = 1; i <= n; i++) printf("%d\n", girl_match[i]);
    }

}GS;
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        GS.read();
        GS.solve();
        GS.print();
        if (t) printf("\n");
    }


    return 0;
}