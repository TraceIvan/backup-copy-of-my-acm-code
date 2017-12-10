#include<iostream>
#include<cmath>
using namespace std;
int main()
{
    int y;
    while (~scanf("%d", &y)&&y)
    {
        int n = (y - 1940) / 10;
        double re = pow(2.0,1.0*n)*log(2.0);
        double sum = 0;
        for(int i=1;;i++)
        {
            sum += log(1.0*i);
            if (sum > re)
            {
                printf("%d\n", i - 1);
                break;
            }
        }
    }
    return 0;
}