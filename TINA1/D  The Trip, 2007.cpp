//���⣺����С�Ĵ����Ŀ��ͬʱʹÿ���������С������Ŀ��С
//��Ȼ����ͬ��С�İ�ֻ�ܷ��ڲ�ͬ�Ĵ�����ô��С�Ĵ����Ŀ������ͬ��С�İ��������Ŀ��֮��ÿ��������С����
#include<iostream>
#include<algorithm>
using namespace std;
int dm[10005];
int main()
{
    int k = 1,n;
    while (cin >> n, n != 0)
    {
        for (int i = 0; i < n; i++) cin >> dm[i];
        sort(dm, dm + n);
        int maxt = 1;
        for (int i = 1, t = 1; i < n; i++)
        {
            if (dm[i] == dm[i - 1]) t++;
            else
            {
                if (t > maxt) maxt = t;
                t = 1;
            }
        }
        if (t > maxt) maxt = t;
        if (k > 1) cout << endl;
        cout << maxt << endl;
        for (int i = 0; i < maxt; i++)
        {
            for (int j = i; j < n; j += maxt)
            {
                if (j == i) cout << dm[j];
                else cout << ' ' << dm[j];
            }
            cout << endl;
        }
        k++;
    }
    return 0;
}