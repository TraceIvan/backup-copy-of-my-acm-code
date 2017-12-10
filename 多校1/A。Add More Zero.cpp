#include<iostream>
#include<cmath>
using namespace std;
int main()
{
    int k=1;
    int m;
    while (~scanf("%d", &m))
    {
            int ans = ceil(1.0*m*log10(2))-1;
            printf("Case #%d: %d\n",k, ans);
            k++;
    }
    return 0;
}
