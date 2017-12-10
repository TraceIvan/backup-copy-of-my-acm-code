#include<iostream>
using namespace std;
int main()
{
    int s, v1, v2, t1, t2;
    while (~scanf("%d%d%d%d%d", &s, &v1, &v2, &t1, &t2))
    {
        int tt1 = v1*s + 2 * t1;
        int tt2 = v2*s + 2 * t2;
        if (tt1 < tt2)printf("First\n");
        else if (tt2 < tt1)printf("Second\n");
        else printf("Friendship\n");

    }


    return 0;
}