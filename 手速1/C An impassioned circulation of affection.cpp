//��һ��ѭ��ö����ĸ���ڶ���ѭ��ö���ڼ䳤�ȣ�������ѭ��ö���������ʼλ�á�
//ÿ��ͳ�Ƴ���ǰ�����ڵ�ǰ��ĸ�ĸ���cnt��lenth��ʾ���䳤�ȣ�f[i][length - cnt] = max(f[i][length - cnt], length);
#include<iostream>
#include<cstdio>
#include<memory.h>
#include<algorithm>
using namespace std;
int n,q;
int dp[30][1600];//��i����ĸ�޸�j���ܴﵽ����󳤶�
char s[1600];
int main()
{
    while (~scanf("%d",&n))
    {
        scanf("%s",s);
        memset(dp, 0, sizeof(dp));
        for (char c = 'a'; c <= 'z'; c++)
        {//ö����ĸ
            int i = c - 'a';
            for (int len = 1; len <= n; len++)
            {//ö�����䳤��
                int cnt = 0;
                for (int j = 0; j < len; j++) if (s[j] == c) cnt++;
                for (int st = 0; st <= n - len; st++)
                {
                    dp[i][len - cnt] = max(dp[i][len - cnt], len);
                    if (st + len < n&&s[st + len] == c) cnt++;
                    if (s[st] == c) cnt--;
                }
            }
        }
        for (int i = 0; i < 26; i++)
        {
            for (int j = 1; j <= n; j++) dp[i][j] = max(dp[i][j], dp[i][j - 1]);
        }
        scanf("%d", &q);
        int tms;
        char cr[5];
        for (int i = 0; i < q; i++)
        {
            scanf("%d%s", &tms, cr);
            printf("%d\n", dp[cr[0] - 'a'][tms]);
        }
    }
    return 0;
}
