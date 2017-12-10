//一个长度n的队列可以看成一个n - 1的队列再追加的1个小孩，这个小孩只可能是：
//a.男孩，任何n - 1的合法队列追加1个男孩必然是合法的，情况数为f[n - 1]；
//b.女孩，在前n - 1的以女孩为末尾的队列后追加1位女孩也是合法的，我们可以转化为n - 2的队列中追加2位女孩；
//一种情况是在n - 2的合法队列中追加2位女孩，情况数为f[n - 2]；
//但我们注意到本题的难点，可能前n - 2位以女孩为末尾的不合法队列（即单纯以1位女孩结尾），也可以追加2位女孩成为合法队列，而这种n - 2不合法队列必然是由n - 4合法队列 + 1男孩 + 1女孩的结构，即情况数为f[n - 4]。
//f[n] = f[n - 1] + f[n - 2] + f[n - 4]
#include<iostream>
#include<cstring>
using namespace std;
int f[1010][1010];
int length[1010];
void Init()
{
    memset(f, 0, sizeof(f));
    f[1][0] = 1;
    f[2][0] = 2;
    f[3][0] = 4;
    f[4][0] = 7;
    int len = 1;
    length[1] = length[2] = length[3] = length[4] = 1;
    for (int i = 5; i <= 1000; i++)
    {
        for (int j = 0; j < len; j++)
        {
            f[i][j] += f[i - 1][j] + f[i - 2][j] + f[i - 4][j];
            f[i][j + 1] += f[i][j] / 10000;
            f[i][j] %= 10000;
        }
        while (f[i][len]) len++;
        length[i] = len;
    }
}
int main()
{
    Init();
    int n;
    while (~scanf("%d", &n))
    {
        int len = length[n];
        printf("%d", f[n][len - 1]);
        for (int i = len - 2; i >= 0; i--) printf("%04d", f[n][i]);
        printf("\n");
    }
    return 0;
}