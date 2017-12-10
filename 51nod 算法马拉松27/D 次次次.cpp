#include<iostream>
using namespace std;
int n;
const int maxn = 100010;
struct node
{
    int max;
    int dmax;
    int min;
    int dmin;
    int v;
}tree[maxn*4];
void Create(int root,int l,int r)
{
    if (l == r)
    {
        scanf("%d", &tree[root].v);
        tree[root].max = tree[root].min = tree[root].dmin = tree[root].dmax = tree[root].v;
        return;
    }
    int mid = (l + r) / 2;
}
int main()
{



    return 0;
}