//�����κ�������x, ��Լ���ĸ�������g(x).����g(1) = 1, g(6) = 4.���ĳ��������x���㣺��������i(0<i<x), ����g(i)<g(x), ���xΪ��������
//����һ:һ���������������ӱ�Ȼ�Ǵ�2��ʼ����������.
//���ʶ�:p = 2 ^ t1 * 3 ^ t2 * 5 ^ t3 * 7 ^ t4.....��Ȼt1 >= t2 >= t3 >= ....
//һ����k=p1^(a1)*p1^(a1)*......pn^(an) (Ψһ�ֽⶨ��)����ô����������ĸ�������(a1+1)*(a2+1)*......*(an+1)��
#include <iostream>
#include<algorithm>
typedef long long ll;
using namespace std;
const int MAXP = 16;
const int prime[MAXP] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53 };//��������2~53ʱ�Ѿ�����10^18��������ֻ��Ҫ�ѵ�53����
ll n, res, ans;
void dfs(ll cur, ll num, int key, ll pre)//��ǰֵ/��ǰԼ������/��ǰ���/��һ�����ĸ���
{
    if (key >= MAXP)
    {
        return;
    }
    else
    {
        if (num > ans)
        {
            res = cur;
            ans = num;
        }
        else if (num == ans)    //  ���Լ��������ͬ����ȡ��С����
        {
            res = min(cur, res);
        }

        ll i;
        for (i = 1; i <= pre; i++)
        {//ö�ٵ�ǰ�����ĸ���
            if (cur <= n / prime[key])  //  cur*prime[key]<=n
            {
                cur *= prime[key];
                dfs(cur, num * (i + 1), key + 1, i);
            }
            else
            {
                break;
            }
        }
    }
}

void solve()
{
    res = 1;
    ans = 1;

    dfs(1, 1, 0, 63);
    cout << res << ' ' << ans << endl;
}
int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        cin >> n;
        solve();
    }
    return 0;
}