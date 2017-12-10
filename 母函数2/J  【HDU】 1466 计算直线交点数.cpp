#include<iostream>
using namespace std;
const int maxn = 210;
bool dp[25][maxn];//dp[i][j]��ʾi��ֱ���ཻʱ�Ƿ���j������
void Init()
{
    for (int i = 0; i <= 20; i++) dp[i][0] = true;//���е�ֱ�߶�ƽ��
    for (int i = 2; i <= 20; i++)
    {//i��ֱ��
        for (int j = 1; j < i; j++)
        {//ö�ٺ͵�i�����ཻ�ıߵ���Ŀ
            for (int k = 0; k < maxn; k++)
            {//ö��j���ߵĽ������
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