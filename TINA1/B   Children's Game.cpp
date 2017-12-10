#include<iostream>
#include<string>
#include<string.h>
#include<algorithm>
using namespace std;
string s[55];
int n;
bool Cmp(const string &a, const string &b)
{
    string tmp1 = a + b;
    string tmp2 = b + a;
    if (tmp1 > tmp2) return true;
    else return false;
}
int main()
{
    while (cin >> n, n != 0)
    {
        for (int i = 0; i < n; i++) cin >> s[i];
        sort(s, s + n, Cmp);
        for (int i = 0; i < n; i++)
        {
            cout << s[i];
        }
        cout << endl;
    }
    return 0;
}