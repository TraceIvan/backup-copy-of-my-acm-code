#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
int m,ans,len;
char s[5100];

void solve()
{
    for (int tlen = len; tlen >= 2; tlen--)
    {
        int bitlen = tlen / 2;
        int rear = 1;
        int sum = 0,dlen=0;
        for (int j=1;j<=bitlen;j++)
        {
            sum += abs(s[j] - s[tlen - j + 1]);
            if (sum<= m)
            {
                dlen++;
                ans = max(ans, dlen);
            }
            else
            {
                sum -= abs(s[rear] - s[tlen - rear + 1]);
                sum -= abs(s[j] - s[tlen - j + 1]);//���´�����ƥ��
                j--;
                dlen--;
                rear++;
            }
        }
    }
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &m);
        scanf("%s", s + 1);
        len = strlen(s + 1);
        ans = 0;
        solve();
        reverse(s + 1, s + 1 + len);
        solve();
        printf("%d\n",ans);

    }
    return 0;
}

#include<bits/stdc++.h>
using namespace std;

const int maxn = 2e4 + 10;;
char str[maxn];
int m, len;
int solve()
{
    int ans = 0;
    for (int i = len; i >= 1; --i)//B�Ӵ��Ľ�β��
    {
        int cnt = i / 2 - 1, d = 0, t = 0, p = 0;//cnt��ʾ����A�Ӵ��Ľ�β����d��ʾ���ǵ�ǰ����dis��t��ʾ���Ǵ��ĳ���
        for (int j = 0; j <= cnt; ++j)//j��ʾ����A���Ŀ�ʼ����
        {
            d += abs(str[1 + j] - str[i - j]);///���ĳ���������չ
            if (d > m)//�����ʾ���ǵ�ǰ����dis�������ƣ�������ǰ����٣�Ȼ��Ӻ�������
            {
                d -= abs(str[1 + p] - str[i - p]);
                d -= abs(str[1 + j] - str[i - j]);
                p++;//ǰ���ȥ�Ĵ��ĳ���
                t--;//���ĳ���ҲҪ�仯
                j--;
            }
            else
            {
                t++;
                ans = max(ans, t);
            }
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
    {
        int ans = 0;
        cin >> m >> str + 1;//�ӵ�һλ��ʼ��ֵ
        len = strlen(str + 1);
        ans = max(ans, solve());//�����������ú������һ��������ǰ�����һ���ֽ���ƥ��
        reverse(str + 1, str + len + 1);
        ans = max(ans, solve());//��������÷�����������ԭ��������ǰ�����һ������ƥ��������һ����
        cout << ans << endl;
    }
    return 0;
}