#include<iostream>
using namespace std;
const int maxn = 210;
bool dp[25][maxn];//dp[i][j]表示i条直线相交时是否有j个交点
void Init()
{
    for (int i = 0; i <= 20; i++) dp[i][0] = true;//所有的直线都平行
    for (int i = 2; i <= 20; i++)
    {//i条直线
        for (int j = 1; j < i; j++)
        {//枚举和第i条边相交的边的数目
            for (int k = 0; k < maxn; k++)
            {//枚举j条边的交点情况
                if (dp[j][k]) dp[i][(i - j)*j + k] = true;
            }

        }
    }
}

int main()
{
    Init();
    int n;
    while (~scanf("%d", &n))
    {
        for (int i = 0; i < maxn; i++)
        {
            if (dp[n][i])
            {
                if (i > 0) printf(" ");
                printf("%d", i);
            }
        }
        printf("\n");
    }
    return 0;
}