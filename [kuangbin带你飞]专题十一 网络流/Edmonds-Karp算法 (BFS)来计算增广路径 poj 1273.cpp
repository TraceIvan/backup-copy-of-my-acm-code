//Ford-Fulkerson����
//Ϊʲô��Ford-Fulkerson�����������㷨��ԭ�����ڿ����ö��ַ�ʽʵ����һ������
//��ʽ����Ψһ��
//�������һ�ֻ��ڹ����������(BFS)����������·��P���㷨��Edmonds-Karp�㷨��
#include <iostream>
#include <conio.h>
#include <limits>
#include <queue>

using namespace std;

const int N = 210;
const int INF = INT_MAX; //�����
int n, m, map[N][N], prepath[N], flow[N], start, End;
queue<int> q;   //�Ƚ��ȳ����С������ڱ��ڵ�����˳��

                //�����������
int bfs()
{
    int i, t;
    while (!q.empty()) q.pop();
    memset(prepath, -1, sizeof(prepath));
    prepath[start] = 0;
    flow[start] = INF;
    q.push(start);
    while (!q.empty())
    {
        t = q.front();				//ȡ���е���Ԫ��
        q.pop();					//�Ѷ�����Ԫ�ص���
        if (t == End) break;
        cout << "bfs path=";
        for (i = 1; i <= m; i++)
        {
            if (i != start && prepath[i] == -1 && map[t][i])
            {
                flow[i] = flow[t] < map[t][i] ? flow[t] : map[t][i];
                q.push(i);
                prepath[i] = t;
                cout << t << ", ";
            }
        }
        cout << endl;
    }
    if (prepath[End] == -1)
        return -1;
    return flow[End];                   //һ�α���֮�����������
}

int Edmonds_Karp()
{
    int max_flow = 0, step, now, pre;
    while (true)
    {
        step = bfs();
        if (step == -1) break;		//�Ҳ�����·��ʱ�˳�
        max_flow += step;
        now = End;
        while (now != start)
        {
            pre = prepath[now];
            map[pre][now] -= step;      //��������ߵ�ʵ������
            map[now][pre] += step;      //��ӷ����
            now = pre;
        }
    }
    return max_flow;
}

int main()
{
    //���ڽӾ����ʾͼ���ڽӹ�ϵ����ʼ������Ȩ��Ϊ0
    memset(map, 0, sizeof(map));

    n = 5;    //�ߵ�����
    m = 4;    //�ڵ�����������Ϊ�鿴���㣬�ڵ��Ŵ�1~4���	

              //ͼ�����ӹ�ϵ��ߵ���������
    float edgeCosts[][3] = { { 1, 2, 40 },{ 1, 4, 20 },{ 2, 4, 20 },{ 2, 3, 30 },{ 3, 4, 10 } };
    for (int i = 0; i < n; i++)
        map[(int)edgeCosts[i][0]][(int)edgeCosts[i][1]] = edgeCosts[i][2];

    start = 1;    //����Դ��
    End = m;      //�������

                  //����ͼ�������
    int maxflow = Edmonds_Karp();			//���������
    printf("����������=%d\n", maxflow);	//���
    getch();
    return 0;
}