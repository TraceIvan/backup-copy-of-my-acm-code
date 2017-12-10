#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include<string>
using namespace std;

#define LL __int64
const int maxn = (int)4e5 + 10;
const int INF = (int)1e8;
int ha[9] = { 1,1,2,6,24,120,720,5040,40320 };//���ع�ϣ
int dir[4][2] = { { 1,0 },{ 0,-1 },{ 0,1 },{ -1,0 } };//��d ��l ��r ��u
char d[10] = { "dlru" };
LL dd[2][4] = { { 0,1,2,3 },{ 3,2,1,0 } };
int vis[2][maxn], t, Min_ans;//vis��¼��̵���Ŀ���ʱ��
char ans[maxn], get[maxn];
LL c[2][maxn];//c[i][j]��ʾi״̬�£�j��ϣֵʱ����С·��
LL mm[30];  //mm[i]��ʾ4^i
struct node
{
    int f[3][3];//״̬
    int x, y;//'0'��λ��
    int g;//��ʾ�ڸ���BFS�еĲ���
    int flag;//0��ʾǰBFS��1��ʾ��BFS
    LL path;//4���Ʊ�ʾ��·��
    int hash_num;//hashֵ
};
int get_hash(node e)//����չ����ѹ���ռ䡣
{
    int a[9], i, j, k = 0, ans = 0;
    for (i = 0; i<3; i++)
    {
        for (j = 0; j<3; j++)
            a[k++] = e.f[i][j];
    }
    for (i = 0; i<9; i++)
    {
        k = 0;
        for (j = 0; j<i; j++)
            if (a[j]>a[i])k++;
        ans += ha[i] * k;
    }
    return ans;
}
string get_str(LL c, int flag, int kk)//������ת����·��
{
    int str[100];
    int i, k = 0;
    for (i = 0; i<vis[flag][kk]; i++)
    {
        str[k++] = c % 4;
        c = c / 4;
    }
    string s = "";
    for (i = k - 1; i >= 0; i--)
        s += d[str[i]];
    return s;
}
void bfs(node e, node ee)//˫��bfs
{
    memset(vis, -1, sizeof(vis));
    int i, j, k, xx, yy, dis[2];
    dis[0] = dis[1] = 0;
    node a, b;
    e.hash_num = get_hash(e);
    e.g = 0, e.flag = 0;
    e.path = 0;
    ee.hash_num = get_hash(ee);
    ee.g = 0, ee.flag = 1;
    ee.path = 0;
    vis[0][e.hash_num] = 0;
    vis[1][ee.hash_num] = 0;
    if (e.hash_num == ee.hash_num)
    {
        printf("0\n\n"); return;
    }

    queue<node>q;
    q.push(e);//ѹ�����
    q.push(ee);//ѹ���յ�
    Min_ans = INF;
    LL str;
    string res;
    while (!q.empty())
    {
        e = q.front();
        q.pop();

        for (i = 0; i<4; i++)
        {//�ĸ�����
            a = e;
            a.x = e.x + dir[i][0];
            a.y = e.y + dir[i][1];
            if (a.x<0 || a.y<0 || a.x >= 3 || a.y >= 3)continue;
            swap(a.f[e.x][e.y], a.f[a.x][a.y]);
            k = get_hash(a);
            if (vis[e.flag][k] != -1)//����Ѿ����ʹ�
            {
                if (e.g + 1>vis[e.flag][k])continue;
                else//������Ը��絽��
                {
                    if (e.flag)str = dd[e.flag][i] * mm[e.g] + e.path;//��DFS
                    else str = e.path * 4 + dd[e.flag][i];//ǰDFS
                    if (c[e.flag][k]>str)
                        c[e.flag][k] = str;
                }
            }
            else//û�з��ʹ�
            {
                vis[e.flag][k] = e.g + 1;
                if (e.flag)c[e.flag][k] = dd[e.flag][i] * mm[e.g] + e.path;
                else c[e.flag][k] = e.path * 4 + dd[e.flag][i];
            }
            a.hash_num = k;
            a.g++;
            a.path = c[e.flag][k];
            if (vis[e.flag ^ 1][k] != -1)//�������һ��BFS�г��ֹ�
            {
                //cout<<vis[0][k]+vis[1][k]<<endl;
                //cout<<c[0][k]<<" "<<c[1][k]<<endl;
                string s = get_str(c[0][k], 0, k) + get_str(c[1][k], 1, k);//�õ�·��
                //cout<<s<<endl;
                t = s.length();
                if (t>Min_ans)
                {//�������
                    cout << Min_ans << endl;
                    cout << res << endl;
                    return;
                }
                if (t<Min_ans)
                {//���С��
                    Min_ans = t;
                    res = s;
                }
                else
                {
                    if (res.compare(s)>0)res = s;
                }
            }
            q.push(a);
        }
    }
}
void init()
{//4���Ʊ�ʾ·��
    int i, j, k;
    mm[0] = 1;
    for (i = 1; i <= 30; i++)
        mm[i] = mm[i - 1] * 4;
}
int main()
{
    init();
    char a[30], b[30];
    int T, tt = 0;
    scanf("%d", &T);
    while (T--)
    {
        int i, j, k, n;
        node e, pp;
        scanf("%s", a);
        scanf("%s", b);
        n = strlen(a);
        for (i = 0; i<n; i++)
        {
            if (a[i] == 'X')
            {
                e.f[i / 3][i % 3] = 0; e.x = i / 3; e.y = i % 3;
            }
            else e.f[i / 3][i % 3] = a[i] - '0';
            if (b[i] == 'X')
            {
                pp.f[i / 3][i % 3] = 0; pp.x = i / 3; pp.y = i % 3;
            }
            else pp.f[i / 3][i % 3] = b[i] - '0';
        }
        printf("Case %d: ", ++tt);
        bfs(e, pp);
    }
    return 0;
}
/*


100
738165X42
51674X328
uurdldruruldlurddlurdru
ruuldrdluurdruldlurddru
*/

/*
�������ɣ�
#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;

const int maxn=1e3+10;
int f[maxn],g[maxn];
void random(int t)
{

int i,j,k,m,num=0;
for(i=0;i<t;i++)f[i]=i;
m=t;
for(i=0;i<t;i++)
{
num=rand()%m;
g[i]=f[num];
f[num]=f[m-1];
m--;
}
}
int judge()
{
int i,j,k=0;
for(i=0;i<9;i++)
{
//printf("%c\n",e.c[i]);
if(g[i]==0)continue;
for(j=0;j<i;j++)
{
if(g[j]==0)continue;
if(g[j]>g[i])k++;
}
}
return k%2;
}
int main()
{
freopen("C:\\Documents and Settings\\All Users\\����\\in.txt","w",stdout);
srand(time(NULL));
int i,j,k,n;
printf("200\n");
for(i=0;i<200;i++)
{
random(9);
k=judge();
for(j=0;j<9;j++)
{
if(g[j]==0)
printf("X");
else
printf("%d",g[j]);
}
printf("\n");
do
{
random(9);
}while(k!=judge());
for(j=0;j<9;j++)
{
if(g[j]==0)
printf("X");
else
printf("%d",g[j]);
}
printf("\n");
}
}

*/
