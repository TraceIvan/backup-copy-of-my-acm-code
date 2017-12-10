//h(1) = 1：1个柱子时，放上1之后，2就放不上去了，不满足柱子上相邻的球之和为平方数（1 + 2 = 3，不是平方数）；
//h(2) = 3：2个柱子时，1和2各放在1个柱子上，3可以放在1上面（1 + 3 = 4 = 2 ^ 2）；
//h(i) = h(i - 1) + i + 1：i为奇数时，在i - 1柱子的基础上增加了一个柱子，这时候可以再放i + 1个球；
//h(i) = h(i - 1) + i：i为偶数时，在i - 1柱子的基础上增加了一个柱子，这时候可以再放i个球。
// f(n) = f(n - 1) + (n + 1) / 2 + (n + 1) / 2    (n > 2)
#include<iostream>
using namespace std;
int re[55];
void Init()
{
    re[1] = 1, re[2] = 3;
    for (int i = 3; i <= 50; i++) re[i] = re[i - 1] + (i + 1) / 2 + (i + 1) / 2;
}
int main()
{
    Init();
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        printf("%d\n", re[n]);
    }
    return 0;
}