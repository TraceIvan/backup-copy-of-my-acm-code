#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int cat[110][110];//每一位存放大数的4位
//Catalan数的组合公式为 Cn=C(2n,n) / (n+1);
//递推公式为 h(n) = h(n - 1)*(4 * n - 2) / (n + 1);
int length[110];//记录每一位卡特兰数的位数
const int MOD = 10000;
void Init()
{//求出1~100位卡特兰数
    memset(cat, 0, sizeof(cat));
    cat[1][0] = 1;
    int len = 1;
    length[1] = 1;
    for (int i = 2; i <= 100; i++)
    {
        //乘法
        int r = 0;
        for (int j = 0; j < len; j++)
        {
            int temp = cat[i - 1][j] * (4 * i - 2);
            cat[i][j] = (temp+r)%MOD;
            r = (temp + r) / MOD;
        }
        //进位
        while (r)
        {
            cat[i][len++] = r %MOD;
            r /= MOD;
        }
        //除法
        r = 0;
        for (int j = len - 1; j >= 0; --j)
        {
            int temp = r * MOD + cat[i][j];
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
        printf("%d", cat[n][len - 1]);
        for (int j = len - 2; j >= 0; j--) printf("%.4d", cat[n][j]);
        printf("\n");
    }
    return 0;
}