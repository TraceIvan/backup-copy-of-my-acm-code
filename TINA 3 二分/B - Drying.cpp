#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
bool Cmp(int a, int b)
{//a的优先级小时返回true
    return a < b;
}
int main()
{
    int n, k;
    while (cin >> n)
    {
        vector<int>v;
        for (int i = 0; i < n; i++)
        {
            int temp;
            cin >> temp;
            v.push_back(temp);
        }
        cin >> k;
        make_heap(v.begin(), v.end(),Cmp);
        //for (int i = 0; i < n; i++) cout << v[i] << endl;
        int t = 0;
        vector<int>::iterator it;
        while (v[0] > 0)
        {
            pop_heap(v.begin(), v.end());
            it = v.end() - 1;
            *it = *it < k ? 0 : *it - k;
            for (it = v.begin(); it != v.end()-1; it++) *it=*it-1;
            push_heap(v.begin(), v.end());
            
            t++;
        }
        cout << t << endl;
    }
    return 0;
}