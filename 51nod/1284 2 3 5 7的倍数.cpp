#include<iostream>
using namespace std;
int main()
{
    long long n;
    scanf("%lld", &n);
    printf("%lld\n", n - (n / 2 + n / 3 + n / 5 + n / 7 - n / 2 / 3 - n / 2 / 5 - n / 2 / 7 - n / 3 / 5 - n / 3 / 7 - n / 5 / 7 + n / 2 / 3 / 5 + n / 2 / 3 / 7+n/2/5/7 + n / 3 / 5 / 7 - n / 2 / 3 / 5 / 7));
    return 0;
}