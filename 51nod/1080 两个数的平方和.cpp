#include<iostream>
#include<cmath>
using namespace std;
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        int cnt = 0;
        for (int i = 0; i < sqrt(n); i++)
        {
            int j = floor(sqrt(n - i*i));
            if (i <= j&&i*i + j*j == n)
            {
                cnt++;
                printf("%d %d\n", i, j);
            }
            else
            {
                j = ceil(sqrt(n - i*i));
                if (i <= j&&i*i + j*j == n)
                {
                    cnt++;
                    printf("%d %d\n", i, j);
                }
            }
        }
        if (cnt == 0)printf("No Solution\n");
    }


    return 0;
}