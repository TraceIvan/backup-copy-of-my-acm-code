#include<iostream>
using namespace std;
int nodes[4][3];
int vec[3][3];
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 3; j++) scanf("%d", &nodes[i][j]);
        }
        for (int i = 1; i < 4; i++)
        {
            for (int j = 0; j < 3; j++) vec[i - 1][j] = nodes[i][j] - nodes[i - 1][j];
        }
        int v = vec[0][0] * (vec[1][1] * vec[2][2] - vec[2][1] * vec[1][2]) - vec[0][1] * (vec[1][0] * vec[2][2] - vec[2][0] * vec[1][2]) + vec[0][2] * (vec[1][0] * vec[2][1] - vec[2][0] * vec[1][1]);
        if (v == 0) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}