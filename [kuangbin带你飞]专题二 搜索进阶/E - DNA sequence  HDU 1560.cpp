#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

char str[10][10];//记录n个字符串
int n, ans, deep, Size[10];
char DNA[4] = { 'A','C','G','T' };//一共四种可能

void dfs(int cnt, int *len)
{
    if (cnt > deep)//大于限制的深度，不用往下搜索
        return;
    int maxx = 0;//预计还要匹配的字符串的最大长度
    for (int i = 0; i<n; i++)
    {
        int t = Size[i] - len[i];
        if (t>maxx)
            maxx = t;
    }
    if (maxx == 0)//条件全部满足即为最优解
    {
        ans = cnt;
        return;
    }
    if (cnt + maxx > deep)//剪枝
        return;
    for (int i = 0; i<4; i++)
    {
        int pos[10];//保存在当前字符被选择为构造的字符串的字符时，剩下的字符串开始需要匹配的位置
        int flag = 0;//判断是否有字符串的当前要匹配的位置是该字符
        for (int j = 0; j<n; j++)
        {//枚举每一个字符串，计算pos值
            if (str[j][len[j]] == DNA[i])
            {
                flag = 1;
                pos[j] = len[j] + 1;
            }
            else
                pos[j] = len[j];
        }
        if (flag)//如果匹配的话
            dfs(cnt + 1, pos);//继续搜索
        if (ans != -1)//如果搜索到的话，直接返回
            break;
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        int minn = 0;
        for (int i = 0; i<n; i++)
        {
            cin >> str[i];
            Size[i] = strlen(str[i]);//记录长度
            if (Size[i]>minn)
                minn = Size[i];
        }
        ans = -1;
        deep = minn;//从最短长度开始搜索
        int pos[10] = { 0 };//记录n个字符串目前匹配到的位置
        while (1)
        {
            dfs(0, pos);
            if (ans != -1)
                break;
            deep++;//加深迭代
        }
        cout << ans << endl;
    }
    return 0;
}