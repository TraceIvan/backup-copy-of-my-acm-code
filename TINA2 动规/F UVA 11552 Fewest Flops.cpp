//DP ���л���
#include<map>
#include<string>
#include<iostream>
#include<memory.h>
#include<algorithm>
using namespace std;
#define maxn 1020
int dp[maxn][maxn];
int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int k;
        cin >> k;
        string s;
        cin >> s;
        int l = s.length();
        int tl = l / k;
        map<char, int>m;
        int count = 0;
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < k; i++)
        {
            if (!m[s[i]])
            {
                m[s[i]] = 1;
                count++;
            }
        }
        for (int i = 0; i < k; i++) dp[0][i] = count;
        for (int j = 1; j<tl; j++)
        {
            m.clear();
            count = 0;
            for (int i = 0; i < k; i++)
            {
                if (!m[s[i + j*k]])
                {
                    m[s[i + j*k]] = 1;
                    count++;
                }
            }
            for (int i = 0; i < k; i++) dp[j][i] = l;
            for (int i = 0; i < k; i++)
            {
                for (int l = 0; l < k; l++)
                {
                    if (m[s[l + (j - 1)*k]] && (count == 1 || s[l + (j - 1)*k] != s[i + j*k]))
                    {//���j-1���е�l����ĸ�ڵ�j���г��ֹ������ҵ�j������ĸ����ֻ��һ�ֻ����ж��ֵ����һ����ĸ������
                        dp[j][i] = min(dp[j][i], dp[j - 1][l] + count - 1);
                    }
                    else dp[j][i] = min(dp[j][i], dp[j - 1][l] + count);
                }
            }
        }
        int mincount = l;
        for (int i = 0; i < k; i++) mincount = min(mincount, dp[tl - 1][i]);
        cout << mincount << endl;
    }
    return 0;
}
//DP[i][j]����ǰi���Ե�i���еĵ�j����ĸ��β����Сcent������
//״̬ת�Ʒ���DP[i][j] = min(DP[i - 1][l] + centi - 1) ��β���Ժϲ�
//DP[i][j] = min(DP[i - 1][l] + cent)��β���ɺϲ���
//lΪö�ٵĵ�i - 1�ε�l����ĸ��β��
//
//����ж������ֶ���β��ĸ�Ƿ���Ժϲ���
//���i - 1�εĵ�l����ĸ��i�γ��ֹ�����i�����һ����ĸ����������i��ֻ��һ��cent��������ÿ�ο����������У�����ֻȷ����ÿ�ε����һ����ĸ��������ȫ�����ж��ϲ������ε���β��