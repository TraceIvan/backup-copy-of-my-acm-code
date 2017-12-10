#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int cat[110][110];
//Catalan数的组合公式为 Cn=C(2n,n) / (n+1);
//递推公式为 h(n) = h(n - 1)*(4 * n - 2) / (n + 1);
int length[110];//记录每一位卡特兰数的位数
void Init()
{//求出1~100位卡特兰数
    memset(cat, 0, sizeof(cat));
    cat[1][0] = 1;
    int len = 1;
    length[1] = 1;
    for (int i = 2; i <= 100; i++)
    {
        //乘法
        for (int j = 0; j < len; j++)
        {
            cat[i][j] = cat[i - 1][j] * (4 * i - 2);
        }
        //进位
        int r = 0;
        for (int j = 0; j < len; j++)
        {
            int temp = cat[i][j] + r;
            cat[i][j] = (temp) % 10;
            r = temp / 10;
        }
        while (r)
        {
            cat[i][len++] = r % 10;
            r /= 10;
        }
        //除法
        r = 0;
        for (int j = len - 1; j >= 0; --j)
        {
            int temp = r * 10 + cat[i][j];
            cat[i][j] = temp / (i + 1);
            r = temp % (i + 1);
        }
        //除法结束后高位0处理
        while (cat[i][len - 1] == 0)
        {
            len--;
        }
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
        for (int j = len - 1; j >= 0; j--) printf("%d", cat[n][j]);
        printf("\n");
    }
    return 0;
}