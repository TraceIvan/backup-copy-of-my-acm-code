#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;
int M[105][105];
int n, m;
bool flag = true;
struct Step
{
    char s;
    int i;
    Step(char s0='r',int i0=0):s(s0),i(i0){ }
};
vector<Step>stp;
void SolveX()
{
    for (int i = 0; i < n;)
    {
        bool ctn = true;
        for (int j = 0; j < m; j++) if (M[i][j] == 0) ctn = false;
        if (!ctn)
        {
            i++;
            continue;
        }
        for (int j = 0; j < m; j++)
        {
            M[i][j]--;
        }
        stp.push_back(Step('r', i + 1));
    }
}
void SolveY()
{
    for (int i = 0; i < m;)
    {
        bool ctn = true;
        for (int j = 0; j < n; j++) if (M[j][i] == 0) ctn = false;
        if (!ctn)
        {
            i++;
            continue;
        }
        for (int j = 0; j < n; j++)
        {
            M[j][i]--;
        }
        stp.push_back(Step('c', i + 1));
    }
}
int main()
{
    while (cin>>n>>m)
    {
        stp.clear();
        flag = true;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++) cin >> M[i][j];
        }
        if (n <= m)
        {
            SolveX();
            SolveY();
        }
        else
        {
            SolveY();
            SolveX();

        }
        for (int i = 0;flag&& i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (M[i][j] > 0)
                {
                    flag = false;
                    break;
                }
            }
        }
        if (!flag) cout << -1 << endl;
        else
        {
            int sz = stp.size();
            cout << sz << endl;
            for (int i = sz - 1; i >= 0; --i)
            {
                if (stp[i].s == 'c') printf("col %d\n", stp[i].i);
                else printf("row %d\n", stp[i].i);
            }
        }
    }
    return 0;
}