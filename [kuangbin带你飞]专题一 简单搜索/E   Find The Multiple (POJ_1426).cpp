//����n���ҵ�һ��ֻ��������1��0������ʹ��Ϊn�ı���
#include<iostream>
#include<queue>
using namespace std;
long long ans,n;
bool flag = false;
void DFS(long long t,int k)
{
    if (flag||k>19) return;
    if (t%n == 0)
    {
        flag = true;
        ans = t;
        return;
    }
    DFS(t * 10,k+1);
    if (flag) return;
    DFS(t * 10 + 1,k+1);
}
int main()
{
    while(~scanf("%d",&n))
    {
        if (n == 0) break;
        flag = false;
        DFS(1,1);
        printf("%lld\n",ans);
    }


    return 0;
}