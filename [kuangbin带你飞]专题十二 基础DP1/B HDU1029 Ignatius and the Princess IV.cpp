#include<iostream>
using namespace std;
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        int cal = 0;
        int m;
        int t;
        while (n--)
        {
            scanf("%d", &t);
            if (cal == 0)
            {
                m = t;
                cal++;
            }
            else
            {
                if(t != m)
                {
                    cal--;
                }
                else cal++;
            }
        }
        printf("%d\n", m);
    }



    return 0;
}