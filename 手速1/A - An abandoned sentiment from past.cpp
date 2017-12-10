#include<iostream>
#include<algorithm>
using namespace std;
int a[105], b[105];
int n, k;
bool Cmp(int a, int b)
{
    return a > b;
}
int main()
{
    while (cin >> n >> k)
    {
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < k; i++) cin >> b[i];
        sort(b, b + k, Cmp);
        bool flag = false;
        int j = 0;
        if (a[0] == 0) a[0] = b[j++];
        for (int i = 1; i < n; i++)
        {
            if (a[i] == 0) a[i] = b[j++];
            if (a[i] < a[i - 1])
            {
                flag = true;
                break;
            }
        }
        if (flag) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}