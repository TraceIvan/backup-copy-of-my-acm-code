#include<iostream>
using namespace std;
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        int cnt = 0;
        while(n)
        {
            n /= 5;
            cnt += n; 
        }
        printf("%d\n", cnt);

    }

    return 0;
}