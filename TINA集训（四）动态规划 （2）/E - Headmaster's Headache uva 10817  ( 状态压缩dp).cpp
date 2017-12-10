#include<iostream>
#include<cstring>
#include<string>
#include<sstream>
#include<algorithm>
using namespace std;
const int INF = 0x7f7f7f7f, MAXN = 131;
int s, m, n, teach[MAXN], cost[MAXN], dp[MAXN][1 << 8][1 << 8];

int DP(int i, int s1, int s2)//s1��Ӧ����Ҫһ����ʦ�̵Ŀ�Ŀ,s2��Ӧ�Ѿ��㹻��ʦ�̵Ŀ�Ŀ.״̬��Ϊdp[i][s1][s2]��������i����ʦΪֹ��У��������Ҫ������Ǯ�ﵽĿ�ꡣ��i < m ʱ�����Ǳ���ѡ��״ֻ̬�ܸ���Ϊ�����ʦ����i >= mʱ�� �Ϳ��Ը���Ϊѡ��ѡ��ʦ����״̬��
//s1,s2��Ϊ2��������ÿһλ��ʾ�ÿγ�������ʦ
//s1����ĳ��ѧ�ƻ���Ҫ1����ʦ��ʱ����λ��Ϊ1�������Ϊ0
//s2:��ĳ��ѧ���Ѿ����㹻����ʦ��ʱ����λ��Ϊ1�������Ϊ0
{
    if (i == m + n) return s2 == (1 << s) - 1 ? 0 : INF;  //ÿ����Ŀ������������ʦ�ˣ���ô�Ͳ���Ҫ�ٻ�Ǯ��
    int &ret = dp[i][s1][s2];//����
    if (ret >= 0) return ret;
    ret = INF;
    if (i >= m) ret = DP(i + 1, s1, s2);         //��ѡ
    s2 |= (s1 & teach[i]);                       //��ʦ�̣ܽ����Ҳ�һ����ʦ����ôһ�����㣬ʣ�µľ������������Ŀ�Ŀ
    s1 |= teach[i];                              //����ȥ��û�˽̵Ŀ�Ŀ�϶���ɲ�һ���˽�
    ret = min(ret, cost[i] + DP(i + 1, s1, s2)); //ѡ
    return ret;
}

int main()
{
    while (~scanf("%d%d%d",&s,&m,&n))
    {
        if (s == 0)break;
        cin.get();
        string ss;
        int x;
        for (int i = 0; i < m + n; ++i)
        {
            getline(cin, ss);
            stringstream sss(ss);
            sss >> cost[i];
            teach[i] = 0;
            while (sss >> x)
            {
                teach[i] |= 1 << (x - 1);
            }
        }
        memset(dp, -1, sizeof dp);
        //for (int i = 0; i < m + n; ++i) cout << cost[i] << ':' << teach[i] << endl;
        cout << DP(0, 0, 0) << '\n';
    }
    return 0;
}
