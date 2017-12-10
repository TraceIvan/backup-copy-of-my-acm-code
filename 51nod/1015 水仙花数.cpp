#include<iostream>
using namespace std;
int ppow(int n, int p)
{
    int re = 1;
    for (int i = 1; i <= p; i++) re *= n;
    return re;
}
int is[7] = { 153,370,371,407,1634,8208,9474 };
int main()
{
    int m;
    while (~scanf("%d", &m))
    {
        int i;
        for (i = 0; m>is[i] && i <= 7; i++);
        printf("%d\n", is[i]);

    }



    return 0;
}