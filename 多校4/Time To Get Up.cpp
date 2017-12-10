#include<iostream>
#include<cstdio>
using namespace std;
char num[7][21];
int Judge(int c)
{
    char top = num[0][c + 1];
    char left1 = num[1][c];
    char right1 = num[1][c + 3];
    char mid = num[3][c + 1];
    char left2 = num[4][c];
    char right2 = num[4][c + 3];
    char bottom = num[6][c + 1];
    if (top != 'X')
    {//1、4
        if (left1 == 'X') return 4;
        else return 1;
    }
    else if (mid != 'X')
    {//0、7
        if (left1 == 'X') return 0;
        else return 7;
    }
    else if (left2 == 'X')
    {//2、6、8
        if (left1 != 'X')return 2;
        else if (right1 == 'X') return 8;
        else return 6;
    }
    else//3、5、9
    {
        if (right1 != 'X') return 5;
        else if (left1 == 'X') return 9;
        else return 3;
    }

}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 21; j++) cin >> num[i][j];
        }
        int h1 = Judge(0);
        int h2 = Judge(5);
        int m1 = Judge(12);
        int m2 = Judge(17);
        printf("%d%d:%d%d\n", h1, h2, m1, m2);
    }
    return 0;
}