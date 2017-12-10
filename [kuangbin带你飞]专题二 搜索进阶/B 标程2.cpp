#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include<string>
#define LL long long int
#define MAXN 363880
using namespace std;

int power[15] = { 1,1,2,6,24,120,720,5040,40320,362880,3628800 };
char begi[15], en[15];
int dir[4] = { 3,-1,1,-3 }, pos_b, pos_e;
char word[5] = "dlru";
int visit[MAXN + 10][2];
LL road[MAXN + 10][2], p2[55];

struct node
{
    int step, k, pos_0;
    LL way;
    char temp[15];
    node()
    {
    }
    node(const char a[], const int b, const LL c, const int d, const int e)
    {
        memset(temp, 0, sizeof temp);
        strcpy(temp, a);
        step = b, way = c, k = d, pos_0 = e;
    }
}n;

int Hash(char a[])
{
    int ans = 0, tmp;
    for (int i = 0; i<9; i++)
    {
        tmp = 0;
        for (int j = i + 1; j<9; j++)
            if (a[i]>a[j])
                tmp++;
        ans += tmp*power[8 - i];
    }
    return ans;
}

string get_way(LL a, int b)
{
    int str[100], cnt = 0;
    for (int i = 1; i <= b; ++i)
    {
        str[++cnt] = a % 4;
        a /= 4;
    }
    string ans = "";
    for (int i = cnt; i>0; --i)
        ans += word[str[i]];
    return ans;
}

void bfs()
{
    if (strcmp(begi, en) == 0)
    {
        printf("0\n\n");
        return;
    }
    memset(visit, -1, sizeof visit);
    memset(road, 0, sizeof road);

    queue<node>point;
    point.push(node(begi, 0, 0, 0, pos_b));
    visit[Hash(begi)][0] = 0;
    point.push(node(en, 0, 0, 1, pos_e));
    visit[Hash(en)][1] = 0;

    char temp[15];
    int pos_0, lin, pos, ans = 1 << 30;
    LL tmp;
    string anspath = "";
    while (!point.empty())
    {
        n = point.front();
        pos_0 = n.pos_0;
        strcpy(temp, n.temp);
        point.pop();

        for (int i = 0; i<4; ++i)
        {
            pos = pos_0 + dir[i];
            if (pos>-1 && pos<9 && (pos / 3 == pos_0 / 3 || pos % 3 == pos_0 % 3))
            {
                swap(temp[pos_0], temp[pos]);
                lin = Hash(temp);

                if (visit[lin][n.k] != -1)
                {
                    if (n.step + 1>visit[lin][n.k])
                    {
                        swap(temp[pos_0], temp[pos]);
                        continue;
                    }
                    if (n.k)
                        tmp = (3 - i)*p2[n.step] + n.way;
                    else tmp = n.way * 4 + i;
                    road[lin][n.k] = min(road[lin][n.k], tmp);
                }
                else
                {
                    visit[lin][n.k] = n.step + 1;
                    if (n.k)
                        road[lin][1] = (3 - i)*p2[n.step] + n.way;
                    else road[lin][0] = n.way * 4 + i;
                }

                if (visit[lin][!n.k] != -1)
                {
                    string path = get_way(road[lin][0], visit[lin][0]) + get_way(road[lin][1], visit[lin][1]);
                    int len = path.size();
                    if (len>ans)
                    {
                        printf("%d\n", ans);
                        cout << anspath << endl;
                        return;
                    }
                    else if (ans>len)
                    {
                        ans = len;
                        anspath = path;
                    }
                    else if (anspath>path)
                        anspath = path;
                }
                point.push(node(temp, n.step + 1, road[lin][n.k], n.k, pos));
                swap(temp[pos_0], temp[pos]);
            }
        }
    }
}

int main()
{
    p2[0] = 1;
    for (int i = 1; i <= 28; ++i)
        p2[i] = p2[i - 1] * 4;
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas)
    {
        scanf("%s%s", begi, en);
        for (int i = 0; i<9; ++i)
        {
            if (begi[i] == 'X')
                pos_b = i, begi[i] = '0';
            if (en[i] == 'X')
                pos_e = i, en[i] = '0';
        }
        printf("Case %d: ", cas);
        bfs();
    }
    return 0;
}